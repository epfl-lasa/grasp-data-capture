#include "stdafx.h"
#include "TrackerChannel.h"
#include <iostream>
#include <sstream>
using namespace std;

#include <stdio.h>
#include <NatNetTypes.h>
#include <NatNetClient.h>
#include <conio.h>
#include <winsock2.h>

#include <assert.h>

void MatrixFromQuat(double qx, double qy, double qz, double qw, double rotmat[3][3]);
void __cdecl DataHandler(sFrameOfMocapData* data, void* pUserData);			// receives data from the server
void __cdecl MessageHandler(int msgType, char* msg);		// receives NatNet error mesages
void resetClient();
int CreateClient(int iConnectionType, TrackerChannel*);
unsigned int MyServersDataPort = 3130;
unsigned int MyServersCommandPort = 3131;

int pose2markerSetID(Pose *p);
char** pose2markerNames(Pose *p, int nMarkers);

NatNetClient* theClient;

char szMyIPAddress[128] = "";
char szServerIPAddress[128] = "";

//
// Tracker Data routines
//
TrackerData::TrackerData(string id)
	: ChannelData(id)
{
}

TrackerData::~TrackerData()
{
	for (map<int,OptiTrackData*>::const_iterator it=objects.begin(); it!=objects.end(); ++it) {
		delete it->second;
	}
}

TrackerData::TrackerData(const TrackerData& td)
	: ChannelData(td.id)
{
	for (map<int,OptiTrackData*>::const_iterator it=td.objects.begin(); it!=td.objects.end(); ++it) {
		assert(objects.find(it->first) != objects.end());
		*(objects[it->first]) = *(it->second);
	}

	setTimeStamp(td.hr, td.min, td.sec, td.ms);
}

void TrackerData::update(int id, void *data)
{
	map<int, OptiTrackData*>::iterator it = objects.find(id);
	if (it == objects.end())
		return;

	switch (it->second->type) {
	case OptiTrackData::Type::MARKERSET:
		{
			MarkerSet* m = it->second->getMarkers();
			sMarkerSetData* d = (sMarkerSetData*)data;
			assert(m->nMarkers == d->nMarkers);
			for (int i=0; i< m->nMarkers; i++) {
				//printf("%f\t%f\t%f\n",pos[i][1],pos[i][2],pos[i][3]);
				m->markerPos[i][0] = (double)(d->Markers[i][0]);
				m->markerPos[i][1] = (double)(d->Markers[i][1]);
				m->markerPos[i][2] = (double)(d->Markers[i][2]);
			}
		}
		break;

	case OptiTrackData::Type::POSE:
		{
			Pose *p = it->second->getPose();
			sRigidBodyData *d = (sRigidBodyData*)data;
			double x, y, z, qx, qy, qz, qw;
			double rotmat[3][3];

			x  = d->x;
			y  = d->y;
			z  = d->z;
			qx  = d->qx*-1; // correct qx, qy, qz for left handedness
			qy  = d->qy*-1;
			qz  = d->qz*-1;
			qw  = d->qw;

			// position
			p->matrix[0][3] = x;
			p->matrix[1][3] = y;
			p->matrix[2][3] = z;	

			// orientation
			MatrixFromQuat(qx, qy, qz, qw, rotmat);
			p->sx = qx;
			p->sy = qy;
			p->sz = qz;
			p->sw = qw;
			for(int i=0; i<3; i++)
				for(int j=0; j<3; j++)
					p->matrix[i][j] = rotmat[i][j];

			if (p->nMarkers > 0) {
				int id2 = pose2markerSetID(p);
				map<int, OptiTrackData*>::iterator it2 = objects.find(id2);
				assert(it2 != objects.end());
				MarkerSet* m2 = it2->second->getMarkers();
				assert(m2->nMarkers == p->nMarkers);
				assert(m2->nMarkers <= d->nMarkers);
				for (int i=0; i< p->nMarkers; i++) {
					m2->markerPos[i][0] = (double)(d->Markers[i][0]);	
					m2->markerPos[i][1] = (double)(d->Markers[i][1]);	
					m2->markerPos[i][2] = (double)(d->Markers[i][2]);	
				}
			}
		}
		break;
	}
}

//void TrackerChannel::updatePose(int id, double x, double y, double z, double qx, double qy, double qz, double qw)
//{
//	tdU.setPosition(id, x, y, z);
//	tdU.setOrientation(id, qx, qy, qz, qw);
//}
//
//void TrackerChannel::updateMarkerSet(int id, int n, MarkerData* data)
//{
//	tdU.setMarkers(id, n, data);
//}
//
//void TrackerData::setMarkers(int id, int n, MarkerData* pos)
//{
//	map<int, OptiTrackData*>::iterator it = objects.find(id);
//	if (it == objects.end())
//		return;
//	assert(it->second->type == OptiTrackData::Type::MARKERSET);
//	MarkerSet* m = it->second->getMarkers();
//	assert(m->nMarkers == n);
//
//	for (int i=0; i<n; i++) {
//		//memcpy(m->markerPos, pos, sizeof(float)*3);
//		//printf("%f\t%f\t%f\n",pos[i][1],pos[i][2],pos[i][3]);
//		m->markerPos[i][1] = (double)pos[i][1];
//		m->markerPos[i][2] = (double)pos[i][2];
//		m->markerPos[i][3] = (double)pos[i][3];
//	}
//}
//
//void TrackerData::setPosition(int id, double x, double y, double z)
//{
//	map<int, OptiTrackData*>::iterator it = objects.find(id);
//	if (it == objects.end())
//		return;
//
//	Pose *p = it->second->getPose();
//	p->matrix[0][3] = x;
//	p->matrix[1][3] = y;
//	p->matrix[2][3] = z;
//}
//
//void TrackerData::setOrientation(int id, double x, double y, double z, double w)
//{
//	double rotmat[3][3];
//
//	MatrixFromQuat(x, y, z, w, rotmat);
//
//	map<int, OptiTrackData*>::iterator it = objects.find(id);
//	if (it == objects.end())
//		return;
//
//	Pose *p = it->second->getPose();
//	p->sx = x;
//	p->sy = y;
//	p->sz = z;
//	p->sw = w;
//	for(int i=0; i<3; i++)
//		for(int j=0; j<3; j++)
//			p->matrix[i][j] = rotmat[i][j];
//}


void MatrixFromQuat(double qx, double qy, double qz, double qw, double rotmat[3][3])
{
    rotmat[0][0] = qx*qx + qw*qw - qz*qz - qy*qy ;
    rotmat[0][1] = 2*(qx*qy - qz*qw);
    rotmat[0][2] = 2*(qx*qz + qy*qw);
    rotmat[1][0] = 2*(qx*qy + qz*qw);
    rotmat[1][1] = qy*qy - qx*qx + qw*qw - qz*qz ;
    rotmat[1][2] = 2*(qy*qz - qx*qw);
    rotmat[2][0] = 2*(qx*qz - qy*qw);
    rotmat[2][1] = 2*(qy*qz + qx*qw);
    rotmat[2][2] = qz*qz- qy*qy - qx*qx + qw*qw ;
}

string TrackerData::toString()
{
	stringstream strm;

	for (map<int,OptiTrackData*>::const_iterator it=objects.begin(); it!=objects.end(); ++it) {
		switch (it->second->type) {
		case OptiTrackData::Type::POSE:
			{
				Pose* p = it->second->getPose();
				strm << p->name << endl;
				for(int i=0; i<4; i++)
					for(int j=0; j<4; j++)
						strm << p->matrix[i][j] << ' ';
				strm << endl;		
			}
			break;

		case OptiTrackData::Type::MARKERSET:
			{
				MarkerSet* m = it->second->getMarkers();
				for(int i=0; i<m->nMarkers; i++) {
					strm << m->markerNames[i] << endl;
					strm << m->markerPos[i][0] << ' ' << m->markerPos[i][1] << ' ' << m->markerPos[i][2] << ' ';
					strm << endl;
				}
			}
			break;
		}
	}

	return string(strm.str());
}

void TrackerData::toBottle(Bottle& b)
{
	for (map<int,OptiTrackData*>::const_iterator it=objects.begin(); it!=objects.end(); ++it) {
		switch (it->second->type) {
		case OptiTrackData::Type::POSE:
			{
				Pose* p = it->second->getPose();

				b.addString(p->name.c_str());
				Bottle& b1 = b.addList();
				for(int i=0; i<4; i++)
					for(int j=0; j<4; j++)
						b1.addDouble(p->matrix[i][j]);
			}
			break;

		case OptiTrackData::Type::MARKERSET:
			{
				MarkerSet *m = it->second->getMarkers();
				for(int i=0; i<m->nMarkers; i++) {
					b.addString(m->markerNames[i].c_str());
					Bottle& b1 = b.addList();
					b1.addDouble(m->markerPos[i][0]);
					b1.addDouble(m->markerPos[i][1]);
					b1.addDouble(m->markerPos[i][2]);
				}
			}
			break;
		}
	}
}

int TrackerData::toBuffer(byte *b)
{
	int idsz;
	long start = (long)b, end;
	
	idsz = id.length() + 1;
	memcpy((void*)b, (void*)id.c_str(), idsz); b = b + idsz;

	//BYTE *bstart = b;
	memcpy((void*)b, (void*) &hr, sizeof(int)); b += sizeof(int);
	memcpy((void*)b, (void*) &min, sizeof(int)); b += sizeof(int);
	memcpy((void*)b, (void*) &sec, sizeof(int)); b += sizeof(int);
	memcpy((void*)b, (void*) &ms, sizeof(int)); b += sizeof(int);

	//assert( *(int *)bstart < 24 && *(int *)(bstart+4) < 60 && *(int*)(bstart+8) < 60 && *(int*)(bstart+12) < 1000);
	
	for (map<int,OptiTrackData*>::const_iterator it=objects.begin(); it!=objects.end(); ++it) {
		switch (it->second->type) {
		case OptiTrackData::Type::POSE:
			{
				Pose *p = it->second->getPose();

				idsz = p->name.length() + 1;
				memcpy((void*)b, (void*)p->name.c_str(), idsz); b = b + idsz;

				int msz = sizeof(p->matrix);
				memcpy((void*)b, &msz, sizeof(int)); b = b + sizeof(int);

				memcpy((void *)b, (void *)&p->matrix[0][0], msz); b = b + msz;
			}
			break;
		case OptiTrackData::Type::MARKERSET:
			{
				MarkerSet *m = it->second->getMarkers();

				for (int i=0; i<m->nMarkers; i++) {
					idsz = m->markerNames[i].length() + 1;
					memcpy((void*)b, (void*)m->markerNames[i].c_str(), idsz); b = b + idsz;

					int msz = sizeof(double)*3;
					memcpy((void*)b, &msz, sizeof(int)); b = b + sizeof(int);

					memcpy((void *)b, (void *)m->markerPos[i], msz); b = b + msz;
				}
			}
			break;
		}
	}
	
	//printf("%d %d %d %d", *(int *)bstart, *(int *)(bstart+4), *(int*)(bstart+8),*(int*)(bstart+16));
	//assert( *(int *)bstart < 24 && *(int *)(bstart+4) < 60 && *(int*)(bstart+8) < 60 && *(int*)(bstart+12) < 1000);

	end = (long)b;

	return end-start;
}

//
//  TrackerChannel routines
//
TrackerChannel::TrackerChannel(string myipad, string serveripad)
	: DataChannel("Optitrack"), tdA("optitrack"), tdU("optitrack"), myipaddress(myipad), serveripaddress(serveripad)
{	
	ghMutex = CreateMutex( 
		NULL,              // default security attributes
		FALSE,             // initially not owned
		NULL
	);             // unnamed mutex

    if (ghMutex == NULL) 
    {
        printf("CreateMutex error: %d\n", GetLastError());        
    }
}

TrackerChannel::~TrackerChannel(void)
{
	CloseHandle(ghMutex);
	stop();
}

int TrackerChannel::doStart(void)
{
    int iResult;
    int iConnectionType = ConnectionType_Multicast;
    //int iConnectionType = ConnectionType_Unicast;
    
	strcpy(szMyIPAddress, myipaddress.c_str());
    strcpy(szServerIPAddress, serveripaddress.c_str());		// not specified - assume server is local machine	
    printf("Connecting to server at %s\n", serveripaddress);

    // Create NatNet Client
    iResult = CreateClient(iConnectionType, this);
    if(iResult != ErrorCode_OK)
    {
        printf("Error initializing client.  See log for details.  Exiting. \n");
        return 0;
    }
    else
    {
        printf("Client initialized and ready.\n");
    }


	// send/receive test request
	printf("[SampleClient] Sending Test Request\n");
	void* response;
	int nBytes;
	iResult = theClient->SendMessageAndWait("TestRequest", &response, &nBytes);
	if (iResult == ErrorCode_OK)
	{
		printf("[SampleClient] Received: %s", (char*)response);
	}

	// Retrieve Data Descriptions from server
	printf("\n\n[SampleClient] Requesting Data Descriptions...");
	sDataDescriptions* pDataDefs = NULL;
	int nBodies = theClient->GetDataDescriptions(&pDataDefs);
	if(!pDataDefs)
	{
		printf("[SampleClient] Unable to retrieve Data Descriptions.");
		return 0;
	}
	else
	{
        printf("[SampleClient] Received %d Data Descriptions:\n", pDataDefs->nDataDescriptions );
        for(int i=0; i < pDataDefs->nDataDescriptions; i++)
        {
            printf("Data Description # %d (type=%d)\n", i, pDataDefs->arrDataDescriptions[i].type);
            if(pDataDefs->arrDataDescriptions[i].type == Descriptor_MarkerSet)
            {
                // MarkerSet
 /*               sMarkerSetDescription* pMS = pDataDefs->arrDataDescriptions[i].Data.MarkerSetDescription;
				if(strcmp(pMS->szName, "All") == 0) {
					printf("MarkerSet Name : %s\n", pMS->szName);
					for(int i=0; i < pMS->nMarkers; i++)
						printf("%s\n", pMS->szMarkerNames[i]);

					registerMarkerSettoTrack(new MarkerSet(MarkerSet::MarkerSetID_ALL, pMS->nMarkers, pMS->szMarkerNames), MarkerSet::MarkerSetID_ALL);
				}*/
            }
            else if(pDataDefs->arrDataDescriptions[i].type == Descriptor_RigidBody)
            {
                // RigidBody
                sRigidBodyDescription* pRB = pDataDefs->arrDataDescriptions[i].Data.RigidBodyDescription;
                printf("RigidBody Name : %s\n", pRB->szName);
                printf("RigidBody ID : %d\n", pRB->ID);
                printf("RigidBody Parent ID : %d\n", pRB->parentID);
                printf("Parent Offset : %3.2f,%3.2f,%3.2f\n", pRB->offsetx, pRB->offsety, pRB->offsetz);

				if (strcmp(pRB->szName, "wrist_root") == 0) {				// wrist_root
					registerPosetoTrack("wrist_root", pRB->ID, 0);
				}
				
				if (strcmp(pRB->szName, "thumb_root") == 0) {               // thumb_root
					registerPosetoTrack("thumb_root", pRB->ID, 0);
				}

				if (strcmp(pRB->szName, "ee_root") == 0) {            //leftHand
					registerPosetoTrack("ee_root", pRB->ID, 3);
				}

				if (strcmp(pRB->szName, "shoulder_root") == 0) {
					registerPosetoTrack("shoulder_root", pRB->ID, 0);
				}

				if (strcmp(pRB->szName, "upperArm_root") == 0) {
					registerPosetoTrack("upperArm_root", pRB->ID, 0);
				}

				if (strcmp(pRB->szName, "bottlecap_root") == 0) {
					registerPosetoTrack("bottlecap_root", pRB->ID, 0);
				}

				if (strcmp(pRB->szName, "bowl_root") == 0) {
					registerPosetoTrack("bowl_root", pRB->ID, 0);
				}

				if (strcmp(pRB->szName, "ftsensor_root") == 0) {
					registerPosetoTrack("ftsensor_root", pRB->ID, 0);
				}

				if (strcmp(pRB->szName, "tool_root") == 0) {
					registerPosetoTrack("tool_root", pRB->ID, 0);
				}

				if (strcmp(pRB->szName, "support_root") == 0) {
					registerPosetoTrack("support_root", pRB->ID, 0);
				}

				if (strcmp(pRB->szName, "hand5_root") == 0) {
					registerPosetoTrack("hand5_root", pRB->ID, 3);
				}

				if (strcmp(pRB->szName, "elbow5_root") == 0) {
					registerPosetoTrack("elbow5_root", pRB->ID, 3);
				}				

				if (strcmp(pRB->szName, "right_shoulder5_root") == 0) {
					registerPosetoTrack("right_shoulder5_root", pRB->ID, 3);
				}

				if (strcmp(pRB->szName, "neck5_root") == 0) {
					registerPosetoTrack("neck5_root", pRB->ID, 3);
				}

				if (strcmp(pRB->szName, "chest5_root") == 0) {
					registerPosetoTrack("chest5_root", pRB->ID, 3);
				}

				if (strcmp(pRB->szName, "waist5_root") == 0) {
					registerPosetoTrack("waist5_root", pRB->ID, 3);
				}

				if (strcmp(pRB->szName, "left_shoulder5_root") == 0) {
					registerPosetoTrack("left_shoulder5_root", pRB->ID, 3);
				}


				////////////////
				
				if (strcmp(pRB->szName, "elbow6_root") == 0) {
					registerPosetoTrack("elbow6_root", pRB->ID, 3);
				}				

				if (strcmp(pRB->szName, "neck6_root") == 0) {
					registerPosetoTrack("neck6_root", pRB->ID, 3);
				}

				if (strcmp(pRB->szName, "chest6_root") == 0) {
					registerPosetoTrack("chest6_root", pRB->ID, 3);
				}

				if (strcmp(pRB->szName, "waist6_root") == 0) {
					registerPosetoTrack("waist6_root", pRB->ID, 3);
				}

				if (strcmp(pRB->szName, "left_shoulder6_root") == 0) {
					registerPosetoTrack("left_shoulder6_root", pRB->ID, 3);
				}

				///////////////////
				//if (strcmp(pRB->szName, "test4_root") == 0) {
				//	registerPosetoTrack("test4_root", pRB->ID, 4);
				//}

				if (strcmp(pRB->szName, "Big_Ball_root") == 0) {
					registerPosetoTrack("Big_Ball_root", pRB->ID, 0);
				}
				if (strcmp(pRB->szName, "Right_hand_root") == 0) {
					registerPosetoTrack("Right_hand_root", pRB->ID, 0);
				}
				if (strcmp(pRB->szName, "Left_hand_root") == 0) {
					registerPosetoTrack("Left_hand_root", pRB->ID, 0);
				}

            }
            else if(pDataDefs->arrDataDescriptions[i].type == Descriptor_Skeleton)
            {
                // Skeleton
                sSkeletonDescription* pSK = pDataDefs->arrDataDescriptions[i].Data.SkeletonDescription;
                printf("Skeleton Name : %s\n", pSK->szName);
                printf("Skeleton ID : %d\n", pSK->skeletonID);
                printf("RigidBody (Bone) Count : %d\n", pSK->nRigidBodies);
                for(int j=0; j < pSK->nRigidBodies; j++)
                {
                    sRigidBodyDescription* pRB = &pSK->RigidBodies[j];
                    printf("  RigidBody Name : %s\n", pRB->szName);
                    printf("  RigidBody ID : %d\n", pRB->ID);
                    printf("  RigidBody Parent ID : %d\n", pRB->parentID);
                    printf("  Parent Offset : %3.2f,%3.2f,%3.2f\n", pRB->offsetx, pRB->offsety, pRB->offsetz);
                }
            }
            else
            {
                printf("Unknown data type.");
                // Unknown
            }
        }      
	}
	
	// Ready to receive marker stream!
	printf("\nTracker Client is connected to server and listening for data...\n");
	return 1;
}

int pose2markerSetID(Pose *p)
{
	return p->id * 100;
}

char** pose2markerNames(Pose *p, int nMarkers)
{
	char** names;
	names = new char*[nMarkers];
	for (int i=0; i< nMarkers; i++)
	{
		stringstream nm;
		int len;
		nm << p->name << "_" << i+1;
		string namei = string(nm.str());
		len = namei.length() + 1;
		names[i] = new char[len];
		strcpy(names[i], namei.c_str());
	}

	return names;
}

void TrackerChannel::registerPosetoTrack(char* name, int id, int nMarkers) 
{
	Pose *pa = new Pose(name, id, nMarkers);
	Pose *pu = new Pose(name, id, nMarkers);

	tdA.objects[id] = new OptiTrackData(OptiTrackData::Type::POSE, pa);
	tdU.objects[id] = new OptiTrackData(OptiTrackData::Type::POSE, pu);

	if (nMarkers > 0) {
		// register marker set for this rigid body
		int id = pose2markerSetID(pa);
		char** names = pose2markerNames(pa, nMarkers);		
		registerMarkerSettoTrack(new MarkerSet(id, nMarkers, names), id);
		
		for (int i=0; i<nMarkers; i++) 
			delete [] names[i];
		delete names;
	}
}

void TrackerChannel::registerMarkerSettoTrack(MarkerSet* mset, int id)
{
	tdA.objects[id] = new OptiTrackData(OptiTrackData::Type::MARKERSET, mset);
	tdU.objects[id] = new OptiTrackData(OptiTrackData::Type::MARKERSET, mset);
}

int TrackerChannel::doStop(void)
{
	if (theClient)
		theClient->Uninitialize();

	delete theClient;
	theClient = NULL;

	cout << "Tracker channel stopped" << endl;
	return 1;
}

void TrackerChannel::startUpdate(void)
{
	DWORD dwWaitResult;

	dwWaitResult = WaitForSingleObject( 
		ghMutex,    // handle to mutex
		INFINITE    // no time-out interval
	);
	setTimestamp(&tdU);
}

// IMP: This must be called between startUpdate and endUpdate
void TrackerChannel::doUpdate(int id, void* data)
{
	tdU.update(id, data);
}

void TrackerChannel::endUpdate(void)
{
	ReleaseMutex(ghMutex);
}

ChannelData* TrackerChannel::getLatest()
{
	DWORD dwWaitResult;
	
    dwWaitResult = WaitForSingleObject( 
        ghMutex,    // handle to mutex
        INFINITE    // no time-out interval
	);
	
	for (map<int,OptiTrackData*>::const_iterator itU=tdU.objects.begin(); itU!=tdU.objects.end(); ++itU) {
		map<int,OptiTrackData*>::iterator itA = tdA.objects.find(itU->first);
		assert(itA != tdA.objects.end());
		*(itA->second) = *(itU->second);
	}
	tdA.setTimeStamp(tdU.hr, tdU.min, tdU.sec, tdU.ms);
	
	ReleaseMutex(ghMutex);	

	return &tdA;
}


//
// Optitrack routines
//
// Establish a NatNet Client connection
int CreateClient(int iConnectionType, TrackerChannel *trackerChannel)
{
    // release previous server
    if(theClient)
    {
        theClient->Uninitialize();
        delete theClient;
    }

    // create NatNet client
    theClient = new NatNetClient(iConnectionType);

    // [optional] use old multicast group
    //theClient->SetMulticastAddress("224.0.0.1");

    // print version info
    unsigned char ver[4];
    theClient->NatNetVersion(ver);
    // printf("NatNet Sample Client (NatNet ver. %d.%d.%d.%d)\n", ver[0], ver[1], ver[2], ver[3]);

    // Set callback handlers
    theClient->SetMessageCallback(MessageHandler);
    theClient->SetVerbosityLevel(Verbosity_Error);
    theClient->SetDataCallback(DataHandler,  trackerChannel);	// this function will receive data from the server

    // Init Client and connect to NatNet server
    // to use NatNet default port assigments
    int retCode = theClient->Initialize(szMyIPAddress, szServerIPAddress);
    // to use a different port for commands and/or data:
    //int retCode = theClient->Initialize(szMyIPAddress, szServerIPAddress, MyServersCommandPort, MyServersDataPort);
    if (retCode != ErrorCode_OK)
    {
        printf("Unable to connect to server.  Error code: %d. Exiting\n", retCode);
        return ErrorCode_Internal;
    }
    else
    {
        // print server info
        sServerDescription ServerDescription;
        memset(&ServerDescription, 0, sizeof(ServerDescription));
        theClient->GetServerDescription(&ServerDescription);
        if(!ServerDescription.HostPresent)
        {
            printf("Unable to connect to server. Host not present. Exiting.\n");
            return ErrorCode_Internal;
        }
        printf("[SampleClient] Server application info:\n");
        printf("Application: %s (ver. %d.%d.%d.%d)\n", ServerDescription.szHostApp, ServerDescription.HostAppVersion[0],
            ServerDescription.HostAppVersion[1],ServerDescription.HostAppVersion[2],ServerDescription.HostAppVersion[3]);
        printf("NatNet Version: %d.%d.%d.%d\n", ServerDescription.NatNetVersion[0], ServerDescription.NatNetVersion[1],
            ServerDescription.NatNetVersion[2], ServerDescription.NatNetVersion[3]);
        printf("Client IP:%s\n", szMyIPAddress);
        printf("Server IP:%s\n", szServerIPAddress);
        printf("Server Name:%s\n\n", ServerDescription.szHostComputerName);
    }

	theClient->SetVerbosityLevel(0);
    return ErrorCode_OK;
}

// DataHandler receives data from the server
void __cdecl DataHandler(sFrameOfMocapData* data, void* pUserData)
{
	//NatNetClient* pClient = (NatNetClient*) pUserData;
	TrackerChannel* trackerChannel = (TrackerChannel*) pUserData;

	//printf("Received frame %d\n", data->iFrame);
	int i=0;

    // same system latency test
    float fThisTick = (float)GetTickCount();
    float fDiff = fThisTick - data->fLatency;
    double dDuration = fDiff;
    //printf("Latency (same system) (msecs): %3.2lf\n", dDuration);


	trackerChannel->startUpdate();


	// Other Markers
	//printf("Other Markers [Count=%d]\n", data->nOtherMarkers);
	//for(i=0; i < data->nOtherMarkers; i++)
	//{
	//	printf("Other Marker %d : %3.2f\t%3.2f\t%3.2f\n",
	//		i,
	//		data->OtherMarkers[i][0],
	//		data->OtherMarkers[i][1],
	//		data->OtherMarkers[i][2]);
	//}

	// MarkerSet data
	//for(i=0; i < data->nMarkerSets; i++)
	//{
	//	if (strcmp(data->MocapData[i].szName, "All") == 0) {
	//		for (int j=0; j<data->MocapData[i].nMarkers	; j++) {
	//				//memcpy(m->markerPos, pos, sizeof(float)*3);
	//				printf("%f\t%f\t%f\n",  
	//							data->MocapData[i].Markers[j][1],
	//							data->MocapData[i].Markers[j][2],
	//							data->MocapData[i].Markers[j][3]);
	//			}
	//		//trackerChannel->doUpdate(MarkerSet::MarkerSetID_ALL, (void*)&data->MocapData[i]);
	//		//trackerChannel->updateMarkerSet(MarkerSet::MarkerSetID_ALL, data->MocapData[i].nMarkers, data->MocapData[i].Markers);
	//	}
	//}

	// Rigid Bodies
	//printf("Rigid Bodies [Count=%d]\n", data->nRigidBodies);
	for(i=0; i < data->nRigidBodies; i++)
	{
		//printf("Rigid Body [ID=%d  Error=%3.2f]\n", data->RigidBodies[i].ID, data->RigidBodies[i].MeanError);
		//printf("\tx\ty\tz\tqx\tqy\tqz\tqw\n");
		//printf("\t%3.2f\t%3.2f\t%3.2f\t%3.2f\t%3.2f\t%3.2f\t%3.2f\n",
		//	data->RigidBodies[i].x,
		//	data->RigidBodies[i].y,
		//	data->RigidBodies[i].z,
		//	data->RigidBodies[i].qx,
		//	data->RigidBodies[i].qy,
		//	data->RigidBodies[i].qz,
		//	data->RigidBodies[i].qw);

		trackerChannel->doUpdate(data->RigidBodies[i].ID, (void*)&data->RigidBodies[i]);

		//printf("\tRigid body markers [Count=%d]\n", data->RigidBodies[i].nMarkers);
		//for(int iMarker=0; iMarker < data->RigidBodies[i].nMarkers; iMarker++)
		//{
  //          printf("\t\t");
  //          if(data->RigidBodies[i].MarkerIDs)
  //              printf("MarkerID:%d", data->RigidBodies[i].MarkerIDs[iMarker]);
  //          if(data->RigidBodies[i].MarkerSizes)
  //              printf("\tMarkerSize:%3.2f", data->RigidBodies[i].MarkerSizes[iMarker]);
  //          if(data->RigidBodies[i].Markers)
  //              printf("\tMarkerPos:%3.2f,%3.2f,%3.2f\n" ,
  //                  data->RigidBodies[i].Markers[iMarker][0],
  //                  data->RigidBodies[i].Markers[iMarker][1],
  //                  data->RigidBodies[i].Markers[iMarker][2]);
  //      }
	}

    // skeletons
    //printf("Skeletons [Count=%d]\n", data->nSkeletons);
 /*   for(i=0; i < data->nSkeletons; i++)
    {
        sSkeletonData skData = data->Skeletons[i];
        printf("Skeleton [ID=%d  Bone count=%d]\n", skData.skeletonID, skData.nRigidBodies);
        for(int j=0; j< skData.nRigidBodies; j++)
        {
            sRigidBodyData rbData = skData.RigidBodyData[j];
            printf("Bone %d\t%3.2f\t%3.2f\t%3.2f\t%3.2f\t%3.2f\t%3.2f\t%3.2f\n",
                    rbData.ID, rbData.x, rbData.y, rbData.z, rbData.qx, rbData.qy, rbData.qz, rbData.qw );
    
            printf("\tRigid body markers [Count=%d]\n", rbData.nMarkers);
            for(int iMarker=0; iMarker < data->RigidBodies[i].nMarkers; iMarker++)
            {
                printf("\t\t");
                if(rbData.MarkerIDs)
                    printf("MarkerID:%d", rbData.MarkerIDs[iMarker]);
                if(rbData.MarkerSizes)
                    printf("\tMarkerSize:%3.2f", rbData.MarkerSizes[iMarker]);
                if(rbData.Markers)
                    printf("\tMarkerPos:%3.2f,%3.2f,%3.2f\n" ,
                    data->RigidBodies[i].Markers[iMarker][0],
                    data->RigidBodies[i].Markers[iMarker][1],
                    data->RigidBodies[i].Markers[iMarker][2]);
            }
        }
    }	*/

	trackerChannel->endUpdate();
}

// MessageHandler receives NatNet error/debug messages
void __cdecl MessageHandler(int msgType, char* msg)
{
	printf("\n%s\n", msg);
}

void resetClient()
{
	int iSuccess;

	printf("\n\nre-setting Client\n\n.");

	iSuccess = theClient->Uninitialize();
	if(iSuccess != 0)
		printf("error un-initting Client\n");

	iSuccess = theClient->Initialize(szMyIPAddress, szServerIPAddress);
	if(iSuccess != 0)
		printf("error re-initting Client\n");
}
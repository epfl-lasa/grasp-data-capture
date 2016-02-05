#pragma once
#include "DataChannel.h"
#include "NatNetTypes.h"
#include <map>


class Pose 
{
public:
	Pose(string name, int id, int nMarkers) { 
		this->name = name; this->id = id; this->nMarkers = nMarkers; sx = sy = sz = sw = 0; 
		memset(matrix, 0, sizeof(matrix));
		for (int i=0; i<4; i++)
			for (int j=0; j<4; j++)
				if (i==j) {
					matrix[i][j] = 1;
					matrix[i][j] = 1;
				}	
	}
	Pose(const Pose& p) { 
		id = p.id; name = p.name; sx = p.sx; sy = p.sy; sz = p.sz; sw = p.sw; memcpy(matrix, p.matrix, sizeof(matrix)); nMarkers = p.nMarkers; 
	}

	int id;
	string name;
	double sx, sy, sz, sw;  // quarternion orientation	 
	double matrix[4][4];   // homogeneous transformation matrix, rotation and translation
	int nMarkers;
};

class MarkerSet {
public: 
	static const int MarkerSetID_ALL = -99;

	MarkerSet(int id, int n, char** names) {
		initMarkerSet(id, n, names);
	}
	~MarkerSet() {
		for (int i=0; i<nMarkers; i++) 
			delete [] markerPos[i];
		delete [] markerPos;
		delete [] markerNames;
	}	
	MarkerSet(const MarkerSet& p) { 
		initMarkerSet(p.id, p.nMarkers, p.markerNames, p.markerPos);
	}
	void initMarkerSet(int id, int n, char** names) {
		this->id = id;
		nMarkers = n;
		markerNames = new string[n];
		markerPos = new double*[n];		
		for(int i=0; i<n; i++) {
			markerNames[i] = names[i];
			markerPos[i] = new double[3];
			markerPos[i][0] = 0;
			markerPos[i][1] = 0;
			markerPos[i][2] = 0;
		}		
	}
	void initMarkerSet(int id, int n, string* names, double** mp) {
		this->id = id;
		nMarkers = n;
		markerNames = new string[n];
		markerPos = new double*[n];		
		for(int i=0; i<n; i++) {
			markerNames[i] = names[i];
			markerPos[i] = new double[3];
			markerPos[i][0] = mp[i][0];
			markerPos[i][1] = mp[i][1];
			markerPos[i][2] = mp[i][2];
		}
	}

	int nMarkers;
	int id;
	string* markerNames;  
	double** markerPos;
};

class OptiTrackData
{	
public:
	enum Type { POSE, MARKERSET };

	OptiTrackData(Type t, void* d) {
		this->type = t;
		this->data = d;
	}
	Pose* getPose() {
		if(type != OptiTrackData::Type::POSE) 
			return NULL;
		return (Pose*)data;
	}
	MarkerSet* getMarkers() {
		if (type != OptiTrackData::Type::MARKERSET)
			return NULL;
		return (MarkerSet*)data;
	}

	Type type;
	void *data;
};


class TrackerData : public ChannelData
{
friend class TrackerChannel;
public:
	TrackerData(string id);
	TrackerData(const TrackerData& td);
	~TrackerData();
	string toString();	
	void toBottle(Bottle& b);
	int toBuffer(byte* b);
	void update(int id, void* data);
	//void setPosition(int id, double x, double y, double z);
	//void setOrientation(int id, double x, double y, double z, double w);
	//void setMarkers(int id, int n, MarkerData* pos);
	
private:
	map<int, OptiTrackData*> objects;
};

class TrackerChannel : public DataChannel
{
protected:
	int doStart();
	int doStop();

public:
	TrackerChannel(string myipaddress, string severipaddress);
	~TrackerChannel(void);

	void startUpdate(void);
	void endUpdate(void);
	void doUpdate(int id, void *data);
	//void updatePose(int id, double x, double y, double z, double qx, double qy, double qz, double qw);
	//void updateMarkerSet(int id, int n, MarkerData* data);


	ChannelData* getLatest();

private:
	void registerPosetoTrack(char* name, int id, int nMarkers);
	void registerMarkerSettoTrack(MarkerSet* mset, int id);

	string myipaddress, serveripaddress;
	TrackerData tdA; // for public access
	TrackerData tdU; // for asynchronous update
	HANDLE ghMutex;  // mutex for synchronization of access to tdU
};


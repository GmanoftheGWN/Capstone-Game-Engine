#ifndef FOLLOW_A_PATH_H
#define FOLLOW_A_PATH_H

#include "KinematicArrive.h"
#include "Path.h"

class FollowAPath : public KinematicArrive {
	private:
		Path* path;

	public:
		FollowAPath(Ref<Actor> character_, Ref<Actor> target_, float radius_, Path* path_);
		virtual ~FollowAPath();
		virtual SteeringOutput* getSteering();
		virtual KinematicSteeringOutput* getKinematicSteering();

		Path* getPath() { return path; }
};

#endif //FollowAPath.h
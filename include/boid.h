#ifndef BOID_H
#define BOID_H

#include "vec.h"
#include <cstddef>

//#define PERCEPTION_RADIUS 7
//#define MAX_ACC 15
//#define MAX_SPEED 20
//#define BOUNDARY 50
extern float ALIGNMENT_PERCEPTION_RADIUS;
extern float COHESION_PERCEPTION_RADIUS;
extern float SEPARATION_PERCEPTION_RADIUS;
extern float MAX_ACC;
extern float MAX_SPEED;
extern float BOUNDARY;

extern float ALIGNMENT_MULT;
extern float COHESION_MULT;
extern float SEPARATION_MULT;

namespace Boid {
	class Boid {
		public:
			Vec::Vec pos;
			Vec::Vec vel;
			Vec::Vec acc;

			Boid();

			void flock(Boid* boids[], size_t num_boids);
			void update(float delta);
		private:
			float gen_pos_float();
			float gen_float();

			void wrap_edges();
			Vec::Vec get_avg_vel_of_nearby_boids(Boid* boids[], size_t num_boids);
			Vec::Vec align(Boid* boids[], size_t num_boids);
			Vec::Vec get_avg_pos_of_nearby_boids(Boid* boids[], size_t num_boids);
			Vec::Vec cohere(Boid* boids[], size_t num_boids);
			Vec::Vec get_avg_inverse_square_pos_of_nearby_boids(Boid* boids[], size_t num_boids);
			Vec::Vec separate(Boid* boids[], size_t num_boids);
	};
}

#endif

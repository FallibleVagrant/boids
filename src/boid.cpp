#include "boid.h"

#include <cstdlib>

float ALIGNMENT_PERCEPTION_RADIUS = 7;
float COHESION_PERCEPTION_RADIUS = 7;
float SEPARATION_PERCEPTION_RADIUS = 7;
float MAX_ACC = 15;
float MAX_SPEED = 20;
float BOUNDARY = 50;

float ALIGNMENT_MULT = 1;
float COHESION_MULT = 1;
float SEPARATION_MULT = 1;

namespace Boid {
	float Boid::gen_pos_float(){
		return ((float)(rand() % 20)) / 5;
	}

	float Boid::gen_float(){
		if(rand() & 1){
			return rand();
		}
		else{
			return -rand();
		}
	}

	Boid::Boid(){
		pos.x = gen_float();
		pos.y = gen_float();
		pos.limit(rand() % (int)BOUNDARY);

		vel.x = gen_float();
		vel.y = gen_float();
		vel.limit(MAX_SPEED);

		acc.x = 0;
		acc.y = 0;
	}

	Vec::Vec Boid::get_avg_vel_of_nearby_boids(Boid* boids[], size_t num_boids){
		Vec::Vec avg;
		float counted_boids = 0;

		for(size_t i = 0; i < num_boids; i++){
			if(boids[i] != this){
				float d = this->pos.dist(boids[i]->pos);

				if(d <= ALIGNMENT_PERCEPTION_RADIUS){
					avg.add(boids[i]->vel);
					counted_boids++;
				}
			}
		}

		avg.div(counted_boids);

		return avg;
	}

	Vec::Vec Boid::align(Boid* boids[], size_t num_boids){
		Vec::Vec avg = this->get_avg_vel_of_nearby_boids(boids, num_boids);
		
		//Average speed of the flock always appears to be going MAX_SPEED.
		avg.set_mag(MAX_SPEED);
		//Direction we shall steer towards is desired_velocity - current_velocity: velocity vector pointing from this to desired_velocity.
		//The average speed (max magnitude) is our desired_velocity.
		avg.sub(this->vel);

		//Limit steering.
		avg.limit(MAX_ACC);

		return avg;
	}

	Vec::Vec Boid::get_avg_pos_of_nearby_boids(Boid* boids[], size_t num_boids){
		Vec::Vec avg;
		float counted_boids = 0;

		for(size_t i = 0; i < num_boids; i++){
			if(boids[i] != this){
				float d = this->pos.dist(boids[i]->pos);

				if(d <= COHESION_PERCEPTION_RADIUS){
					avg.add(boids[i]->pos);
					counted_boids++;
				}
			}
		}

		avg.div(counted_boids);

		return avg;
	}

	Vec::Vec Boid::cohere(Boid* boids[], size_t num_boids){
		Vec::Vec avg = get_avg_pos_of_nearby_boids(boids, num_boids);
		
		avg.sub(this->pos);
		avg.set_mag(MAX_SPEED);
		avg.sub(this->vel);

		avg.limit(MAX_ACC);

		return avg;
	}

	Vec::Vec Boid::get_avg_inverse_square_pos_of_nearby_boids(Boid* boids[], size_t num_boids){
		Vec::Vec avg;
		float counted_boids = 0;

		for(size_t i = 0; i < num_boids; i++){
			if(boids[i] != this){
				float d = this->pos.dist(boids[i]->pos);

				if(d <= SEPARATION_PERCEPTION_RADIUS){
					Vec::Vec diff(this->pos);
					diff.sub(boids[i]->pos);

					//diff is inversely proportional to the distance.
					//Inverse square!
					diff.div(d * d);

					avg.add(diff);
					counted_boids++;
				}
			}
		}

		avg.div(counted_boids);

		return avg;
	}

	Vec::Vec Boid::separate(Boid* boids[], size_t num_boids){
		Vec::Vec avg = get_avg_inverse_square_pos_of_nearby_boids(boids, num_boids);
		
		avg.set_mag(MAX_SPEED);
		avg.sub(this->vel);

		avg.limit(MAX_ACC);

		return avg;
	}

	void Boid::wrap_edges(){
		if(this->pos.x > BOUNDARY){
			this->pos.x = -BOUNDARY;
		}
		else{
			if(this->pos.x < -BOUNDARY){
				this->pos.x = BOUNDARY;
			}
		}
		if(this->pos.y > BOUNDARY){
			this->pos.y = -BOUNDARY;
		}
		else{
			if(this->pos.y < -BOUNDARY){
				this->pos.y = BOUNDARY;
			}
		}
	}

	void Boid::flock(Boid* boids[], size_t num_boids){
		this->acc.mult(0);

		this->wrap_edges();
		Vec::Vec alignment(this->align(boids, num_boids));
		Vec::Vec cohesion(this->cohere(boids, num_boids));
		Vec::Vec separation(this->separate(boids, num_boids));

		alignment.mult(ALIGNMENT_MULT);
		cohesion.mult(COHESION_MULT);
		separation.mult(SEPARATION_MULT);

		this->acc.add(alignment);
		this->acc.add(cohesion);
		this->acc.add(separation);
	}

	void Boid::update(float delta){
		//update pos
		Vec::Vec temp(vel.x, vel.y);
		temp.mult(delta);
		pos.add(temp);

		//update vel
		temp.set(acc);
		temp.mult(delta);
		vel.add(temp);
		vel.set_mag(MAX_SPEED);
	}
}

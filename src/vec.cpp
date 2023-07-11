#include "vec.h"

#include <cmath>

namespace Vec {
	Vec::Vec(float x, float y){
		this->x = x;
		this->y = y;
	}

	Vec::Vec() : Vec(0, 0) {}

	Vec::Vec(const Vec& other){
		this->x = other.x;
		this->y = other.y;
	}

	void Vec::set(Vec& other){
		this->x = other.x;
		this->y = other.y;
	}

	void Vec::add(Vec& other){
		this->x += other.x;
		this->y += other.y;
	}

	void Vec::sub(Vec& other){
		this->x -= other.x;
		this->y -= other.y;
	}

	void Vec::mult(float num){
		this->x *= num;
		this->y *= num;
	}

	void Vec::div(float num){
		if(num != 0){
			this->x /= num;
			this->y /= num;
		}
	}

	float Vec::dist(Vec& other){
		float result_x = powf(this->x - other.x, 2);
		float result_y = powf(this->y - other.y, 2);
		float result = result_x + result_y;

		return sqrtf(result);
	}

	float Vec::get_mag(){
		return sqrtf(powf(this->x, 2) + powf(this->y, 2));
	}

	void Vec::set_mag(float new_mag){
		float current_mag = get_mag();

		if(current_mag == 0){
			return;
		}

		this->div(current_mag);
		this->mult(new_mag);
	}

	void Vec::limit(float lim){
		if(get_mag() > lim){
			this->set_mag(lim);
		}
	}
}

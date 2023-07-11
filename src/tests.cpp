#include <iostream>
#include <cassert>

#include "boid.h"

bool floats_roughly_equal(float x, float y, float epsilon){
	float largest = x > y ? x : y;
	float smallest = x < y ? x : y;

	return (largest - smallest) < epsilon;
}

bool rough_eq(float x, float y){
	return floats_roughly_equal(x, y, 0.001);
}

#define assert_req(x, y) (assert(rough_eq(x, y)))

#define assert_veq(i, j)		\
	assert_req(i.x, j.x);		\
	assert_req(i.y, j.y);

void rough_equal_works(){
	assert(rough_eq(3.0f, 3.000000001f));
	assert(!rough_eq(3.1f, 3.2f));

	assert_req(3.0f, 3.000000001f);
}

void vec_constructor_works(){
	Vec::Vec test(5, 7);
	assert(test.x == 5);
	assert(test.y == 7);

	Vec::Vec test_again(3.3, -3.3);
	assert_req(test_again.x, 3.3);

	assert_req(test_again.y, -3.3);

	Vec::Vec test_test;
	assert_req(test_test.x, 0);
	assert_req(test_test.y, 0);
}

void vec_set(){
	Vec::Vec zero_vector;
	Vec::Vec one_one(1, 1);

	zero_vector.set(one_one);
	assert_veq(zero_vector, one_one);
}

void vec_add(){
	Vec::Vec zero_vector;
	Vec::Vec one_one(1, 1);

	zero_vector.add(one_one);
	assert_veq(zero_vector, one_one);

	Vec::Vec random(33.33, 55.27);
	random.add(one_one);
	Vec::Vec expected(34.33, 56.27);
	assert_veq(random, expected);
}

void vec_sub(){
	Vec::Vec random(5.3, 0.7);
	Vec::Vec one_one(1, 1);

	random.sub(one_one);

	Vec::Vec expected(4.3, -0.3);
	assert_veq(random, expected);
}

void vec_mult(){
	Vec::Vec random(5.3, 0.7);
	Vec::Vec zero_vector;

	random.mult(0);

	assert_veq(random, zero_vector);

	Vec::Vec random_two(5.3, 0.7);
	Vec::Vec random_three(-5.3, -0.7);

	random_two.mult(-1);

	assert_veq(random_two, random_three);

	Vec::Vec test(2.1, 3.3);
	Vec::Vec test_expected(4.62, 7.26);

	test.mult(2.2);

	assert_veq(test, test_expected);
}

void vec_div(){
	Vec::Vec random(5.3, 0.7);
	Vec::Vec expected(5.3, 0.7);

	//Should do nothing.
	random.div(0);

	random.div(1);

	assert_veq(random, expected);

	Vec::Vec random_two(5.3, 0.7);
	Vec::Vec random_three(-5.3, -0.7);

	random_two.div(-1);

	assert_veq(random_two, random_three);

	Vec::Vec test(3.3, 2.2);
	Vec::Vec test_expected(0.6179, 0.4119);

	test.div(5.34);
}

void vec_dist(){
	Vec::Vec one_one(1, 1);
	Vec::Vec one_two(1, 2);

	assert_req(one_one.dist(one_two), 1);

	Vec::Vec random(37.578, 93.43);

	assert_req(random.dist(random), 0);

	Vec::Vec zero_vector;

	assert_req(random.dist(zero_vector), 100.7038);
	
	Vec::Vec random_two(3.3, 2.2);

	assert_req(random.dist(random_two), 97.457140);
}

void vec_set_mag(){
	Vec::Vec zero_one(0, 1.1);
	Vec::Vec expected(0, 2.2);

	zero_one.set_mag(2.2);

	assert_veq(zero_one, expected);
}

void vec_tests(){
	vec_constructor_works();
	vec_set();
	vec_add();
	vec_sub();
	vec_mult();
	vec_div();
	vec_dist();
	vec_set_mag();
}

void boid_tests(){

}

int main(){
	rough_equal_works();
	vec_tests();
	boid_tests();
}

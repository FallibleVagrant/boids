#ifndef VEC_H
#define VEC_H

namespace Vec {
	class Vec {
		public:
			float x;
			float y;

			Vec(float x, float y);
			Vec();
			Vec(const Vec& other);

			void set(Vec& other);
			void add(Vec& other);
			void sub(Vec& other);
			void mult(float num);
			void div(float num);
			float dist(Vec& other);
			void set_mag(float mag);
			void limit(float lim);
		private:
			float get_mag();
	};
}

#endif

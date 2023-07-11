#include "Application.h"

#include "imgui.h"
#include "implot.h"

#include "boid.h"
#include <cstdlib>
#include <ctime>

#define NUM_BOIDS 100

namespace MyApp{
	static size_t num_boids = NUM_BOIDS;

	//Plot needs an array of xy points.
	static float plot_x[NUM_BOIDS];
	static float plot_y[NUM_BOIDS];

	static Boid::Boid* boids[NUM_BOIDS];

	void setup(){
		srand(std::time(nullptr));
		for(size_t i = 0; i < num_boids; i++){
			boids[i] = new Boid::Boid;
		}
	}

	void draw(){
		ImGui::ShowDemoWindow();
		ImPlot::ShowDemoWindow();

		float delta = ImGui::GetIO().DeltaTime;

		for(size_t i = 0; i < num_boids; i++){
			boids[i]->flock(boids, num_boids);
			boids[i]->update(delta);
		}

		for(size_t i = 0; i < num_boids; i++){
			plot_x[i] = boids[i]->pos.x;
			plot_y[i] = boids[i]->pos.y;
		}
		
		ImGui::Begin("Graph");
		if(ImPlot::BeginPlot("Scatter Plot")){
			ImPlot::PlotScatter("Boids", plot_x, plot_y, num_boids);
			ImPlot::EndPlot();
		}
		ImGui::End();

		ImGui::Begin("Settings");
		ImGui::Button("\n\n\n\n                    Hello                          \n\n\n\n");
		static float value = 0;
		ImGui::DragFloat("Value", &value);
		ImGui::SliderFloat("Alignment Perception Radius", &ALIGNMENT_PERCEPTION_RADIUS, 0.0f, 50.0f, "ratio = %.3f");
		ImGui::SliderFloat("Cohesion Perception Radius", &COHESION_PERCEPTION_RADIUS, 0.0f, 50.0f, "ratio = %.3f");
		ImGui::SliderFloat("Separation Perception Radius", &SEPARATION_PERCEPTION_RADIUS, 0.0f, 50.0f, "ratio = %.3f");
		ImGui::SliderFloat("Max ACC", &MAX_ACC, 0.0f, 50.0f, "ratio = %.3f");
		ImGui::SliderFloat("Max SPD", &MAX_SPEED, 0.0f, 100.0f, "ratio = %.3f");
		ImGui::SliderFloat("Boundary", &BOUNDARY, 0.0f, 150.0f, "ratio = %.3f");
		ImGui::SliderFloat("Alignment Strength", &ALIGNMENT_MULT, 0.0f, 50.0f, "ratio = %.3f");
		ImGui::SliderFloat("Cohesion Strength", &COHESION_MULT, 0.0f, 50.0f, "ratio = %.3f");
		ImGui::SliderFloat("Separation Strength", &SEPARATION_MULT, 0.0f, 50.0f, "ratio = %.3f");
		ImGui::End();
	}
}

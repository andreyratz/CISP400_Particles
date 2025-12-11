#pragma once
#include "Engine.h"
#include <ctime>

using namespace sf;
using namespace std;

Engine::Engine() {
	sf::VideoMode vm = sf::VideoMode::getDesktopMode();
	m_Window.create(vm, "Particles", Style::Default);
}

void Engine::run() {

	sf::Clock clock;

	cout << "Starting Particle unit tests...\n";
	Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
	p.unitTests();
	cout << "Unit tests complete. Starting engine...\n";

	while(m_Window.isOpen()) {
		clock.restart();
		sf::Time time = clock.getElapsedTime();

		input();
		update(time.asSeconds());
		draw();
	}

}

void Engine::input() {

	std::srand(std::time({}));

	while (const optional event = m_Window.pollEvent()) {

		if (event->is<Event::Closed>()) {
			m_Window.close();
		}

		//number of particles generated
		const int NUM_P {5};
		if (const auto* mb = event->getIf<Event::MouseButtonPressed>()) {
			if (mb->button == Mouse::Button::Left) {
				for (int i {0}; i < NUM_P; i++) {
					int numPoints = rand() % 26 + 25;
					Particle newParticle(m_Window, numPoints, sf::Mouse::getPosition(m_Window));
					m_particles.push_back(newParticle);
				}
			}
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::Scan::Escape)) {
		m_Window.close();
	}

}

void Engine::update(float dtAsSeconds) {

	for (std::vector<Particle>::iterator it = m_particles.begin(); it != m_particles.end();) {
		if (it->getTTL() > 0.0) {
			it->update(dtAsSeconds);
			it++;
		}
		else { 
			it = m_particles.erase(it); 
		}
	}

}

void Engine::draw() {

	m_Window.clear();
	for (size_t i {0}; i < m_particles.size(); i++) {
		m_Window.draw(m_particles.at(i));
		m_Window.display();
	}
}


					





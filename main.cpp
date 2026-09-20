#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <optional>

struct particle {
    sf::CircleShape shape;
    sf::Vector2f position;
    sf::Vector2f velocity;
    float radius = 15.f;

    particle(float startX, float startY) {
        shape.setRadius(radius);
        shape.setOutlineColor(sf::Color::Black);
        shape.setFillColor(sf::Color::Black);
        shape.setOutlineThickness(5.f);
        shape.setOrigin({15.f, 15.f});

        position = {startX, startY};
        velocity = {15.f, 0.f}; // Initial velocity
    }
};

int main() {
    // init window
    constexpr unsigned int windowWidth = 800; // constexpr means @ compiled, not runtime -> save memory
    constexpr unsigned int windowHeight = 600;
    sf::RenderWindow window(sf::VideoMode({windowWidth, windowHeight}), "Gravity simulation");

    std::vector<particle> particles;

    particles.push_back(particle(100.f, 50.f));
    particles.push_back(particle(200.f, 50.f));
    particles.push_back(particle(300.f, 50.f));
    particles.push_back(particle(400.f, 50.f));
    particles.push_back(particle(500.f, 50.f));
    particles.push_back(particle(600.f, 50.f));
    particles.push_back(particle(700.f, 50.f));


    sf::Clock clock; // create clock
    while (window.isOpen()) {
        sf::Time elapsed = clock.restart();
        const float deltaTime = elapsed.asSeconds(); // amount of time that passed between the last frame and the current one

        while (const auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
        window.close();
    }
}

        for (int i = 0; i < particles.size(); i++) { //particle &p : particles
            constexpr float gravity = 9.81f;
            const float SF = 100.f; // S.F for pixels

            particle &p = particles[i];
            // Update velocity
            p.velocity.y += gravity * deltaTime;

            // Update position
            p.position.y += p.velocity.y * deltaTime * SF;
            p.position.x += p.velocity.x * deltaTime * SF; // Fixed from velocity.x to position.x

            // Floor Collision
            if (p.position.y > windowHeight - p.radius) {
                p.position.y = windowHeight - p.radius;
                p.velocity.y *= -0.8f;
                if (std::abs(p.velocity.y) < 2.0f) p.velocity.y = 0.0f;
            }

            // Wall Collisions
            if (p.position.x > windowWidth - p.radius) {
                p.position.x = windowWidth - p.radius;
                p.velocity.x *= -0.8f;
                if (std::abs(p.velocity.x) < 2.0f) p.velocity.x = 0.0f;
            } else if (p.position.x < p.radius) {
                p.position.x = p.radius;
                p.velocity.x *= -0.8f;
                if (std::abs(p.velocity.x) < 2.0f) p.velocity.x = 0.0f;
            }

            // Ceiling Collision
            if (p.position.y < p.radius) {
                p.position.y = p.radius;
                p.velocity.y *= -0.8f;
                if (std::abs(p.velocity.y) < 2.0f) p.velocity.y = 0.0f;
            }

            // Particle Collision
            for (int j = i + 1; j < particles.size(); j++) {
                float distanceX = particles[j].position.x - p.position.x;
                float distanceY = particles[j].position.y - p.position.y;
            
                float distance = sqrt(pow(distanceX, 2) + pow(distanceY, 2));

                if (distance < particles[j].radius + particles[i].radius) {
                    float normalX = distanceX / distance;
                    float normalY = distanceY / distance;
                    
                    float overlap = 0.5f * (particles[i].radius + particles[j].radius - distance); // Calculate overlap

                    p.position.x -= overlap * normalX; // Adjust positions to resolve overlap
                    p.position.y -= overlap * normalY;

                    float relativeVelocityX = p.velocity.x - particles[j].velocity.x;
                    float relativeVelocityY = p.velocity.y - particles[j].velocity.y;

                    float dotProduct = (relativeVelocityX * normalX) + (relativeVelocityY * normalY);

                    if (dotProduct < 0) continue; // Prevents particles from sticking together

                    float impulseScalar = -dotProduct; // Equal mass for both particles

                    particles[i].velocity.x += impulseScalar * normalX; // Update velocities based on impulse
                    particles[i].velocity.y += impulseScalar * normalY;

                    particles[j].velocity.x -= impulseScalar * normalX;
                    particles[j].velocity.y -= impulseScalar * normalY;
                }
            }
            



            // Sync shape to math position
            p.shape.setPosition(p.position);
        }

        // Draw
        window.clear(sf::Color::White);
        for (particle &p : particles) {
            window.draw(p.shape);
        }
        window.display();
        }
    return 0;
    }
#include <SFML/System/Vector2.hpp>

namespace ze {
    class Transform {
        friend class PhysicsManager2D;
    public:
        Transform(sf::Vector2f pos, sf::Vector2f scale, float rot) {
            this->m_position = pos;
            this->m_scale = scale;
            this->m_rotation = rot;
        }

        void SetPosition(sf::Vector2f pos) {
            this->m_position = pos;
        }

        void SetScale(sf::Vector2f scale) {
            this->m_scale = scale;
        }

        void SetRotation(float rot) {
            this->m_rotation = rot;
        }

        sf::Vector2f GetPosition() {
            return m_position;
        }

        sf::Vector2f GetScale() {
            return m_scale;
        }

        float GetRotation() {
            return m_rotation;
        }

    private:
        sf::Vector2f m_position;
        sf::Vector2f m_scale;
        float m_rotation;
    };
}

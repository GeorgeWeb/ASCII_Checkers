#ifndef PAWN_HPP
#define PAWN_HPP

// project includes
#include "../Common.hpp"

namespace CheckerZ { namespace API {
	
	enum class PawnState
	{
		CAN_MOVE,
		CAN_JUMP,
		IMMOBILE
	};

	class Pawn
	{
		protected:
			uint8 m_mesh;
			std::string m_color;

			size_t m_x;
			size_t m_y;

		public:
			Pawn() = default;
			Pawn(uint8&& t_mesh, std::string&& t_color, size_t&& t_x, size_t&& t_y) :
				m_mesh(t_mesh),
				m_color(t_color),
				m_x(t_x),
				m_y(t_y)
			{ }

			// manual setting
			void setValues(uint8&& t_mesh, std::string&& t_color, size_t&& t_x, size_t&& t_y)
			{
				m_mesh = t_mesh;
				m_color = t_color;
				m_x = t_x;
				m_y = t_y;
			}

		public:		
			friend bool operator== (const Pawn& t_lhs, const Pawn& t_rhs);
			friend bool operator!= (const Pawn& t_lhs, const Pawn& t_rhs);

			inline uint8& getMesh() { return m_mesh; }
			inline std::string& getColor() { return m_color; }

			inline Position& getPos()& { return std::make_pair(m_x, m_y); }
			inline size_t& getCoordX() { return m_x; }
			inline size_t& getCoordY() { return m_y; }

			inline bool isKing() const { return m_mesh == 'B' || m_mesh == 'R'; }
	};

} }
#endif !PAWN_HPP
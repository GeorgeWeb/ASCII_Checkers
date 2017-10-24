#ifndef PAWN_HPP
#define PAWN_HPP

// project includes
#include "../Common.hpp"

namespace CheckerZ { namespace API {
	
	class Pawn
	{
		public:
			Pawn() = default;
			Pawn(uint8&& t_mesh, std::string&& t_color) :
				m_mesh(std::move(t_mesh)),
				m_color(std::move(t_color))
			{ }

		public:
			virtual const std::string getType() const { return std::string("Pawn"); }
		
		public:
			inline uint8& getMesh() { return m_mesh; }
			inline std::string& getColor() { return m_color; }

			void setValues(uint8&& t_mesh, std::string&& t_color)
			{
				m_mesh = std::move(t_mesh);
				m_color = std::move(t_color);
			}
		
		protected:
			uint8 m_mesh;
			std::string m_color;
	};

} }
#endif !PAWN_HPP
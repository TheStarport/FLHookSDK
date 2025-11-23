#ifndef __FASTDOT_H
#define __FASTDOT_H

#include "Vector.hpp"

class FastDot
{
private:
	typedef float (FastDot::* fd_member_type)(const Vector & v) const;

	const float x, y, z;
	fd_member_type dot_fpt;	// float ( FastDot::* dot_fpt )( const Vector & v ) const;
	int ops_saved;			// from 0 to 5

	inline float dot000( const Vector & v ) const { return                  0.0f; }
	inline float dot001( const Vector & v ) const { return                   v.z; }
	inline float dot00X( const Vector & v ) const { return                 z*v.z; }
	inline float dot010( const Vector & v ) const { return           v.y        ; }
	inline float dot011( const Vector & v ) const { return           v.y +   v.z; }
	inline float dot01X( const Vector & v ) const { return           v.y + z*v.z; }
	inline float dot0X0( const Vector & v ) const { return         y*v.y        ; }
	inline float dot0X1( const Vector & v ) const { return         y*v.y +   v.z; }
	inline float dot0XX( const Vector & v ) const { return         y*v.y + z*v.z; }

	inline float dot100( const Vector & v ) const { return   v.x                ; }
	inline float dot101( const Vector & v ) const { return   v.x +           v.z; }
	inline float dot10X( const Vector & v ) const { return   v.x +         z*v.z; }
	inline float dot110( const Vector & v ) const { return   v.x +   v.y        ; }
	inline float dot111( const Vector & v ) const { return   v.x +   v.y +   v.z; }
	inline float dot11X( const Vector & v ) const { return   v.x +   v.y + z*v.z; }
	inline float dot1X0( const Vector & v ) const { return   v.x + y*v.y        ; }
	inline float dot1X1( const Vector & v ) const { return   v.x + y*v.y +   v.z; }
	inline float dot1XX( const Vector & v ) const { return   v.x + y*v.y + z*v.z; }

	inline float dotX00( const Vector & v ) const { return x*v.x                ; }
	inline float dotX01( const Vector & v ) const { return x*v.x +           v.z; }
	inline float dotX0X( const Vector & v ) const { return x*v.x +         z*v.z; }
	inline float dotX10( const Vector & v ) const { return x*v.x +   v.y        ; }
	inline float dotX11( const Vector & v ) const { return x*v.x +   v.y +   v.z; }
	inline float dotX1X( const Vector & v ) const { return x*v.x +   v.y + z*v.z; }
	inline float dotXX0( const Vector & v ) const { return x*v.x + y*v.y        ; }
	inline float dotXX1( const Vector & v ) const { return x*v.x + y*v.y +   v.z; }
	inline float dotXXX( const Vector & v ) const { return x*v.x + y*v.y + z*v.z; }

	void InitDot( void )
	{
		if(x == 0.0f)
		{
			if(y == 0.0f)
			{
				if(z == 0.0f)
				{
					dot_fpt = &FastDot::dot000;
					ops_saved = 5;
				}else
				if(z == 1.0f)
				{
					dot_fpt = &FastDot::dot001;
					ops_saved = 5;
				}
				else
				{
					dot_fpt = &FastDot::dot00X;
					ops_saved = 4;
				}

			}else
			if(y == 1.0f)
			{
				if(z == 0.0f)
				{
					dot_fpt = &FastDot::dot010;
					ops_saved = 5;
				}else
				if(z == 1.0f)
				{
					dot_fpt = &FastDot::dot011;
					ops_saved = 4;
				}
				else
				{
					dot_fpt = &FastDot::dot01X;
					ops_saved = 3;
				}
			}
			else
			{
				if(z == 0.0f)
				{
					dot_fpt = &FastDot::dot0X0;
					ops_saved = 4;
				}else
				if(z == 1.0f)
				{
					dot_fpt = &FastDot::dot0X1;
					ops_saved = 3;
				}
				else
				{
					dot_fpt = &FastDot::dot0XX;
					ops_saved = 2;
				}
			}
		}else
		if(x == 1.0f)
		{
			if(y == 0.0f)
			{
				if(z == 0.0f)
				{
					dot_fpt = &FastDot::dot100;
					ops_saved = 5;
				}else
				if(z == 1.0f)
				{
					dot_fpt = &FastDot::dot101;
					ops_saved = 4;
				}
				else
				{
					dot_fpt = &FastDot::dot10X;
					ops_saved = 3;
				}

			}else
			if(y == 1.0f)
			{
				if(z == 0.0f)
				{
					dot_fpt = &FastDot::dot110;
					ops_saved = 4;
				}else
				if(z == 1.0f)
				{
					dot_fpt = &FastDot::dot111;
					ops_saved = 3;
				}
				else
				{
					dot_fpt = &FastDot::dot11X;
					ops_saved = 2;
				}
			}
			else
			{
				if(z == 0.0f)
				{
					dot_fpt = &FastDot::dot1X0;
					ops_saved = 3;
				}else
				if(z == 1.0f)
				{
					dot_fpt = &FastDot::dot1X1;
					ops_saved = 2;
				}
				else
				{
					dot_fpt = &FastDot::dot1XX;
					ops_saved = 1;
				}
			}
		}
		else
		{
			if(y == 0.0f)
			{
				if(z == 0.0f)
				{
					dot_fpt = &FastDot::dotX00;
					ops_saved = 4;
				}else
				if(z == 1.0f)
				{
					dot_fpt = &FastDot::dotX01;
					ops_saved = 3;
				}
				else
				{
					dot_fpt = &FastDot::dotX0X;
					ops_saved = 2;
				}

			}else
			if(y == 1.0f)
			{
				if(z == 0.0f)
				{
					dot_fpt = &FastDot::dotX10;
					ops_saved = 3;
				}else
				if(z == 1.0f)
				{
					dot_fpt = &FastDot::dotX11;
					ops_saved = 2;
				}
				else
				{
					dot_fpt = &FastDot::dotX1X;
					ops_saved = 1;
				}
			}
			else
			{
				if(z == 0.0f)
				{
					dot_fpt = &FastDot::dotXX0;
					ops_saved = 2;
				}else
				if(z == 1.0f)
				{
					dot_fpt = &FastDot::dotXX1;
					ops_saved = 1;
				}
				else
				{
					dot_fpt = &FastDot::dotXXX;
					ops_saved = 0;
				}
			}
		}
	}

public:

	inline float dot( const Vector & v ) const { return (this->*dot_fpt)( v ); }

	inline int GetSavedOps( void ) const { return ops_saved; } 

	FastDot(const float _x, const float _y, const float _z) : x(_x), y(_y), z(_z)
	{
		InitDot();
	}

	FastDot(const Vector & _vec) : x(_vec.x), y(_vec.y), z(_vec.z)
	{
		InitDot();
	}
};

#endif
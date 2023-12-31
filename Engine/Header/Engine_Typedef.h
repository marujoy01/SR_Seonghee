#ifndef Engine_Typedef_h__
#define Engine_Typedef_h__

using std::unordered_map;

namespace Engine
{
	typedef		bool						_bool;

	typedef		signed char					_byte;
	typedef		unsigned char				_ubyte;

	typedef		wchar_t						_tchar;
	
	typedef		signed short				_short;
	typedef		unsigned short				_ushort;

	typedef		signed int					_int;
	typedef		unsigned int				_uint;

	typedef		signed long					_long;
	typedef		unsigned long				_ulong;

	typedef		float						_float;
	typedef		double						_double;

	// 아키텍처에 따른 소수점 정밀도 높이기
#ifdef _WIN64
#if _WIN64
	typedef		_double						_real;
#endif // _WIN64 == 1
#else
	typedef		_float						_real;
#endif // _WIN64

	template <typename Key, typename Value>
	using _unmap = unordered_map<Key, Value>;

	typedef		D3DXVECTOR2					_vec2;
	typedef		D3DXVECTOR3					_vec3;
	typedef		D3DXVECTOR4					_vec4;

	typedef		D3DXMATRIX					_matrix;

	/*typedef	 struct tagMyVec3 : public D3DXVECTOR3
	{
		float	Get_Dot(const d3dxvector3& vTemp);
	
	};*/
}

#endif // Engine_Typedef_h__

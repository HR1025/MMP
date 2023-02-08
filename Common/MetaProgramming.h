//
// MetaProgramming.h
//
// Library: Common
// Package: Any
// Module:  MetaProgramming
//
// Note : copy from Foundation/include/Poco/MetaProgramming.h (Poco)
//

#pragma once

namespace Mmp
{


template <typename T>
struct IsReference
	/// Use this struct to determine if a template type is a reference.
{
	enum
	{
		VALUE = 0
	};
};


template <typename T>
struct IsReference<T&>
{
	enum
	{
		VALUE = 1
	};
};


template <typename T>
struct IsReference<const T&>
{
	enum
	{
		VALUE = 1
	};
};


template <typename T>
struct IsConst
	/// Use this struct to determine if a template type is a const type.
{
	enum
	{
		VALUE = 0
	};
};


template <typename T>
struct IsConst<const T&>
{
	enum
	{
		VALUE = 1
	};
};


template <typename T>
struct IsConst<const T>
{
	enum
	{
		VALUE = 1
	};
};


template <typename T, int i>
struct IsConst<const T[i]>
	/// Specialization for const char arrays
{
	enum
	{
		VALUE = 1
	};
};


template <typename T>
struct TypeWrapper
	/// Use the type wrapper if you want to decouple constness and references from template types.
{
	typedef T TYPE;
	typedef const T CONSTTYPE;
	typedef T& REFTYPE;
	typedef const T& CONSTREFTYPE;
};


template <typename T>
struct TypeWrapper<const T>
{
	typedef T TYPE;
	typedef const T CONSTTYPE;
	typedef T& REFTYPE;
	typedef const T& CONSTREFTYPE;
};


template <typename T>
struct TypeWrapper<const T&>
{
	typedef T TYPE;
	typedef const T CONSTTYPE;
	typedef T& REFTYPE;
	typedef const T& CONSTREFTYPE;
};


template <typename T>
struct TypeWrapper<T&>
{
	typedef T TYPE;
	typedef const T CONSTTYPE;
	typedef T& REFTYPE;
	typedef const T& CONSTREFTYPE;
};


} // namespace Mmp
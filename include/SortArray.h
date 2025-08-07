#pragma once
#include <cassert>
#include <vector>

using namespace std;

template<class T> class SortArray
{
public:
	SortArray( int size )
	{
		assert( 0 < size && size <= INT_MAX );
		mArray.reserve( size );
	}

	~SortArray(void)
	{
	}

	void add( T* t )
	{
		assert( mArray.size() < INT_MAX );
		int pos = mArray.size();
		mArray.resize( pos + 1 );
		while( pos > 0 && *mArray[pos-1] < *t )
		{
			mArray[pos] = mArray[pos-1];
			pos--;
		}
		mArray[pos] = t;
	}

	T& get( int idx )
	{
		return *mArray[idx];
	}

	const T& get( int idx ) const
	{
		return *mArray[idx];
	}

	T* operator[]( int i )
	{
		return mArray[i];
	}

	const T* operator[]( int i ) const
	{
		return mArray[i];
	}

	int getSize() const
	{
		return mArray.size();
	}

	void reset()
	{
		mArray.clear();
	}

	SortArray( const SortArray& sa )
	{
		*this = sa;
	}

	SortArray& operator=( const SortArray& sa )
	{
		unsigned srcSize = sa.mArray.size();
		if( mArray.capacity() < srcSize )
		{
			mArray.reserve( srcSize );
		}
		reset();
		for( unsigned i = 0; i < srcSize; i++ )
		{
			mArray.push_back( sa.mArray[i] );
		}
		return *this;
	}

private:
	vector<T*> mArray;
	//生のポインタのポインタでなくvectorを使用する理由
	//SortArrayがコンストラクタ、コピーコンストラクタのどちらで生成されてもmArrayの初期化が行われるようにするため
	//生のポインタのポインタの場合、以下のような不都合がある
	//①コンストラクタを呼び出さないでいきなりコピーコンストラクタを呼び出すとmArrayが初期化されてないのでバグる
	//例えば、関数からコピーを返したり、SortArray a = b;と直接代入するとバグる
	//前者はクラスのメンバであれば参照返しする。後者はSortArray a; a = b;と分けて書く
	//②配列要素はポインタ
	//③配列要素の大小比較に使用する数値が*オペレータで取得可能
	//必ずコンストラクタを呼び出してから使えばOKだが、使う側からしたら不便
};
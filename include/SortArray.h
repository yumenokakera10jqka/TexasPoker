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
	//���̃|�C���^�̃|�C���^�łȂ�vector���g�p���闝�R
	//SortArray���R���X�g���N�^�A�R�s�[�R���X�g���N�^�̂ǂ���Ő�������Ă�mArray�̏��������s����悤�ɂ��邽��
	//���̃|�C���^�̃|�C���^�̏ꍇ�A�ȉ��̂悤�ȕs�s��������
	//�@�R���X�g���N�^���Ăяo���Ȃ��ł����Ȃ�R�s�[�R���X�g���N�^���Ăяo����mArray������������ĂȂ��̂Ńo�O��
	//�Ⴆ�΁A�֐�����R�s�[��Ԃ�����ASortArray a = b;�ƒ��ڑ������ƃo�O��
	//�O�҂̓N���X�̃����o�ł���ΎQ�ƕԂ�����B��҂�SortArray a; a = b;�ƕ����ď���
	//�A�z��v�f�̓|�C���^
	//�B�z��v�f�̑召��r�Ɏg�p���鐔�l��*�I�y���[�^�Ŏ擾�\
	//�K���R���X�g���N�^���Ăяo���Ă���g����OK�����A�g�������炵����s��
};
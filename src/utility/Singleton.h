#ifndef _UTILITY_SINGLETON_H__
#define _UTILITY_SINGLETON_H__

#include <assert.h>

namespace utility {
	template <typename T> class Singleton
	{
	public:
		static T& getSingleton()
		{
			if (!mSingleton) mSingleton = new T;
			assert(mSingleton);
			return *mSingleton;
		}

		static T* getSingletonPtr()
		{
			if (!mSingleton) mSingleton = new T;
			assert(mSingleton);
			return mSingleton;
		}

		static void removeSingleton()
		{
			if (mSingleton)
			{
				delete mSingleton;
				mSingleton = 0;
			}
		}

	protected:
		static T* mSingleton;

		Singleton() {}
		~Singleton() {}

	private:
		Singleton(const Singleton&);
		Singleton& operator = (const Singleton&);
	};

	template <typename T> T* Singleton<T>::mSingleton = 0;

}
#endif

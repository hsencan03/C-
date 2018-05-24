#include <iostream>
#include <limits>
#include <vector>

template<typename T>
class TrackingAllocator {
public:
	//necessary
	using value_type = T;

	using pointer = T * ;
	using const_pointer = const T*;
	using void_pointer = void*;
	using const_void_pointer =const void*;
	using size_type = size_t;
	using difference_type = std::ptrdiff_t;


	template<class U>
	struct rebind
	{
		using other = TrackingAllocator<U>;
	};


	TrackingAllocator() = default;
	//necessary
	template<typename U>
	TrackingAllocator(const TrackingAllocator<U> &other){}

	~TrackingAllocator() = default;
	//necessary
	pointer allocate(size_type numObjects) 
	{
		mAllocations += numObjects;
		return static_cast<pointer>(operator new(sizeof(T)*numObjects));
	}
	pointer allocate(size_type numObject, const_void_pointer hint) 
	{
		return allocate(numObject);
	}
	//necessary
	void deallocate(pointer p, size_type numObject)
	{
		operator delete(p);
	}

	template<class U,class ...Args>
	void construct(U *p, Args &&...args) 
	{
		new(p) U(std::forward<Args>(args)...);
	}

	template<class U>
	void destroy(U *p)
	{
		p->~U();
	}

	size_type get_allocations()const
	{
		return mAllocations;
	}

	size_type max_size()const
	{
		return std::numeric_limits<size_type>::max();
	}

private:
	size_type mAllocations = 0;
};

int main() {

	std::vector<int, TrackingAllocator<int>>v(5);

	std::cout << (v.get_allocator()).get_allocations();

	std::cin.get();
	return 0;

}
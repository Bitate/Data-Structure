#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <vector>
namespace bitate
{
	template<typename data_type>
	class queue
	{
	private:
		size_t queue_size = 0;
		int begin = 0;
		int end = 0;
		data_type* queue_ptr = nullptr;
	public:
		queue()
		{
			queue_ptr = new data_type[1024];
		}
		queue(size_t size) : queue_ptr(new data_type[size])
		{
		}

		void push(const data_type& data)
		{
			if (queue_size < 1024)
			{
				queue_ptr[++end] = data;
				++queue_size;
			}
		}

		void pop()
		{
			if(queue_size > 0)
			{
				--begin;
				--queue_size;
			}
		}

		size_t size() const
		{
			return queue_size;
		}
		
		bool empty() const
		{
			return queue_size == 0;
		}
		
		void clear()
		{
			begin = 0;
			end = 0;
			size_t = 0;
		}
	};

}

#endif
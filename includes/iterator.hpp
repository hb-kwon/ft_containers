#ifndef ITERATOR_HPP
# define ITERATOR_HPP

// #include <iterator>
#include <cstddef>

/**
 * iterator implement
 * reverse_iterator
 * bidirectional or random-access iterator 를 사용해 범위를 통해 반복되는 방향을 반대로 한다,
 *
 *
 * iterator?
 * 요소의 범위(배열, 컨테이너 등)의 일부 요소를 가리키며 연산자 set(증감(+++,--)연산자를 사용)를 사용하여 해당 범위의 요소를 반복할 수 있는 기능을 가진 객체
 *
 * iterator traits
 * 반복자의 속성을 정의하는 클래스, 반복자의 속성에 대해 균일한 인터페이스를 제공한다.
 * iterator_traits의 인스턴스화 멤버를 사용하여 전달된 반복자의 특정 속성 및 그것들이 나타내는 범위를 결정한다.
 *
 * iterator category
 * 반복자가 지원하는 속성을 나타내는 데 사용되는 빈클래스 유형
 *
 * Input/Output
 * -> 가장 제한된 유형의 반복자. 순차적인 싱글패스 입력 또는 출력 작업을 수행할 수 있다.
 *
 * Forward
 * -> input 반복자의 모든 기능을 갖추고 있으며, constant 반복자가 아닌 경우 output 반복자의 기능도 갖추고 있지만 범위(순방향)를 통해 반복하는 방향이 한 방향으로 제한된다. 모든 표준 컨테이너는 최소 순방향 반복자 유형을 지원한다.
 *
 * Bidirectional
 * -> bidirectional 반복자는 forward 반복자와 비슷하지만 거꾸로 반복할 수도 있다.
 *
 * Random Access
 * random access 반복자는 bidirectional 반복자의 모든 기능을 구현하고 비순차적으로 범위에 액세스할 수 있는 기능을 갖추고 있다.
 * distant 요소는 간격의 모든 요소를 반복하지 않고 반복자의 오프셋 값을 적용함으로써 직접 access할 수 있다.
 * 이러한 반복자는 표준 포인터와 유사한 기능을 가지고 있다.(포인터는 이 카테고리의 반복자)
 */

/**
 * @brief iterators_traits
 * iterator_tags & categories
 * iterator를 구분하는데 사용되는 빈 유형
 * 구별은 무엇을 포함하느냐에 의해서가 아니라, 단지 무엇에 의해 만들어진다.
 * 서로 다른 반복자 유형이 지원하는 서로 다른 작업을 기반으로 서로 다른 기본 알고리즘을 사용할 수 있다.
 * Traits class는 iterator의 속성의 정의하는 특성 클래스
 */
namespace ft
{
	/**
	 * @brief category
	 * 각 iterator의 category를 구분하기 위한 빈 클래스
	 */
	struct input_iterator_tag {};	//marking input iterators
	struct output_iterator_tag {};	//marking output iterators
	struct forward_iterator_tag : public input_iterator_tag {};	//Forward iterators support a superset of input iterator operations.
	struct bidirectional_iterator_tag : public forward_iterator_tag {};	//Bidirectional iterators support a superset of forward iterator operations.
	struct random_access_iterator_tag : public bidirectional_iterator_tag {}; //Random-access iterators support a superset of bidirectional iterator operations.

	/**
	 * @brief iterator_traits
	 * iterator 특성들의 type 이름을 고정
	 * iterator의 성격이 달라도 통일해서 사용할 수 있다.
	 */
	// Generic Definition
	template <class Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::iterator_category	iterator_category;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference 			reference;
	};

	//T* specialization
	template <class T>
	struct iterator_traits<T*>
	{
		typedef T			value_type;
		typedef ptrdiff_t	difference_type;
		typedef random_access_iterator_tag iterator_category;
		typedef T*			pointer;
		typedef T&			reference;
	};

	//const T* specialization
	template <class T>
	struct iterator_traits<const T*>
	{
		typedef T value_type;
		typedef ptrdiff_t difference_type;
		typedef random_access_iterator_tag iterator_category;
		typedef const T* pointer;
		typedef const T& reference;
	};

	/**
	 * @brief iterator
	 * iterator 클래스를 파생하는데 사용할 수 있는 기본 클래스 템플릿
	 * 해당 클래스는 iterator클래스가 아니며 iterator가 사용할 것으로 예상되는 기능을 제공하지 않는다.
	 * std::iterator는 반복자에 필요한 유형의 정의를 단순화하기 위해 제공되는 기본 클래스입니다.
	 * std::iterator를 사용하지 못하므로 따로 만들어서 사용
	 * This is a base class template that can be used to derive iterator classes from it.
	 * It is not an iterator class and does not provide any of the functionality an iterator is expected to have.
	 *
	 * @tparam Category		반복자가 속한 카테고리 Category to which the iterator belongs to.
	 * @tparam T			반복자를 참조함으로써 얻을 수 있는 값의 타입, 반복자가 가리키는 요소의 타입 Type of elements pointed by the iterator.
	 * @tparam Distance		반복자 간의 거리를 식별하는데 사용할 수 있는 타입 Type to repreent the difference between two iterators.
	 * @tparam Pointer		(T)에서 반복된 타입에 대한 포인터, 반복자가 가리키는 요소에 대한 포인터 Type to repreent a pointer to an element pointed by the iterator.
	 * @tparam Reference	(T)에서 반복된 타입에 대한 참조, 반복자가 가리키는 요소에 대한 참조 Type to repreent a reference to an element pointed by the iterator.
	 */
	template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct iterator
	{
		typedef T value_type;
		typedef Distance difference_type;
		typedef Pointer pointer;
		typedef Reference reference;
		typedef Category iterator_category;
	};

	/**
	 * @brief reverse iterator
	 * This class reverses the direction in which a bidirectional or random-access iterator iterates through a range.
	 *
	 * @tparam Iterator
	 * A bidirectional iterator type. Or a random-access iterator,
	 * if an operator that requires such a category of iterators is used.
	 */
	template <class Iterator>
	class reverse_iterator
	{
		public:
			typedef Iterator iterator_type;
			typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename iterator_traits<Iterator>::value_type			value_type;
			typedef typename iterator_traits<Iterator>::pointer				pointer;
			typedef typename iterator_traits<Iterator>::reference			reference;
		protected:
			Iterator current;


		public:
			/**
			 * @brief Construct a new reverse iterator object
			 * default constructor
			 * initialization constructor
			 * copy constructor
			 */
			reverse_iterator() : current() {} //default constructor
			explicit reverse_iterator (iterator_type it) : current(it) {} //initialization constructor
			template <class Iter>
			reverse_iterator (const reverse_iterator<Iter>& rev_it) : current(rev_it.base()) {} //copy

			/**
			 * @brief operator
			 */
			//assigns another iterator adaptor
			template <typename Iter>
			reverse_iterator& operator=(const reverse_iterator<Iter>& rev_it) //assignment
			{
				this->current = rev_it.current;
				return (*this);
			}

			//accesses the underlying adaptor
			iterator_type base() const //return base iterator
			{
				return (this->current);
			}

			//accesses the pointed-to-element
			reference operator*() const //dereference iterator
			{
				iterator_type tmp = this->current;
				--tmp;
				return (*tmp);
			}

			pointer operator->() const //dereference iterator
			{
				return ( &(operator*()) );
			}

			//advances or decrements the iterator
			reverse_iterator& operator++() //decrements the base iterator kept by the object (as if applying operator-- to it).
			{
				--this->current;
				return (*this);
			}

			reverse_iterator operator++(int)
			{
				reverse_iterator tmp = *this;
				++(*this);
				return (tmp);
			}

			reverse_iterator& operator--() //increments the base iterator kept by the object (as if applying operator++ to it).
			{
				++this->current;
				return (*this);
			}

			reverse_iterator operator--(int)
			{
				reverse_iterator tmp = *this;
				--(*this);
				return (tmp);
			}

			//현재 위치에서 n만큼 차이나는 위치의 iterator 반환
			//해당 기능들을 사용하기 위해서는 base iterator가 random_access_iterator여야한다. -> 해당 기능을 vector에서 사용하므로 vector_iterator를 random_access_iterator를 사용한다.
			reverse_iterator operator+(difference_type n) const
			{
				return (reverse_iterator(current - n));
			}

			reverse_iterator& operator+=(difference_type n)
			{
				this->current -= n;
				return (*this);
			}

			reverse_iterator operator-(difference_type n) const
			{
				return (reverse_iterator(current + n));
			}

			reverse_iterator& operator-=(difference_type n)
			{
				this->current += n;
				return (*this);
			}

			//accesses an element by index
			//If such an element does not exist, it causes undefined behavior.
			//Internally, the function accesses the proper element of its base iterator, returning the same as: base()[-n-1].
			//iterator가 현재 가리키는 요소에서 n개 위치에 있는 요소에 엑세스한다.
			reference operator[](difference_type n) const
			{
				return (this->current[-n - 1]);
			}
	};

	/**
	 * @brief non-member function overloads
	 *
	 * reverse_iterator 개체 lhs와 rhs 간에 적절한 비교 작업을 수행합니다.
	 * operator on reverse iterators vs equivalent used on base iterators
	 */
	template <class Iter1, class Iter2>
	bool operator==(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
	{
		return ( lhs.base() == rhs.base() );
	}

	template <class Iter1, class Iter2>
	bool operator!=(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
	{
		return ( lhs.base() != rhs.base() );
	}

	template <class Iter1, class Iter2>
	bool operator<(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
	{
		return ( lhs.base() > rhs.base() );
	}

	template <class Iter1, class Iter2>
	bool operator>(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
	{
		return ( lhs.base() < rhs.base() );
	}

	template <class Iter1, class Iter2>
	bool operator>=(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
	{
		return ( lhs.base() <= rhs.base() );
	}

	template <class Iter1, class Iter2>
	bool operator<=(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
	{
		return ( lhs.base() >= rhs.base() );
	}

	template <class Iterator>
	reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& it)
	{
		return ( it.base() + n );
	}

	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return ( rhs.base() - lhs.base() );
	}

	//non-member non-const function overload
	template <class Iter>
	bool operator==(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs)
	{
		return ( lhs.base() == rhs.base() );
	}

	template <class Iter>
	bool operator!=(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs)
	{
		return ( lhs.base() != rhs.base() );
	}

	template <class Iter>
	bool operator<(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs)
	{
		return ( lhs.base() > rhs.base() );
	}

	template <class Iter>
	bool operator>(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs)
	{
		return ( lhs.base() < rhs.base() );
	}

	template <class Iter>
	bool operator>=(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs)
	{
		return ( lhs.base() <= rhs.base() );
	}

	template <class Iter>
	bool operator<=(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs)
	{
		return ( lhs.base() >= rhs.base() );
	}

	template <class Iterator, class Iterator_c>
	typename ft::reverse_iterator<Iterator>::difference_type operator-(const ft::reverse_iterator<Iterator> &lhs, const ft::reverse_iterator<Iterator_c> &rhs)
	{
		return (rhs.base() - lhs.base());
	}
}

#endif

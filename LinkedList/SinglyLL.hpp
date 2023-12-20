#pragma once

#include <iostream>
#include <concepts>

namespace fatpound::linkedlist
{
	template <std::totally_ordered T>
	class SinglyLL
	{
	public:
		SinglyLL() = default;
		virtual ~SinglyLL() noexcept
		{
			if (list_ == nullptr)
			{
				return;
			}

			Node* ex = list_;
			Node* temp;

			do
			{
				temp = ex->next;
				delete ex;

				ex = temp;
			}
			while (ex != nullptr);

			list_ = nullptr;
			end_  = nullptr;

			item_count_ = static_cast<decltype(item_count_)>(0);
		}
		SinglyLL(const SinglyLL<T>& src) = delete;
		SinglyLL(SinglyLL<T>&& src) noexcept
			:
			list_(std::exchange(src.list_, nullptr)),
			end_(std::exchange(src.end_, nullptr)),
			item_count_( std::exchange(src.item_count_, static_cast<decltype(item_count_)>(0)))
		{

		}
		SinglyLL<T>& operator = (const SinglyLL<T>& src) = delete;
		SinglyLL<T>& operator = (SinglyLL<T>&& src) noexcept
		{
			list_ = std::exchange(src.list_, nullptr);
			end_  = std::exchange(src.end_,  nullptr);

			item_count_ = std::exchange(src.item_count_, static_cast<decltype(item_count_)>(0));

			return *this;
		}


	public:
		virtual void Add(T new_item)
		{
			Node* new_part = new Node(new_item);

			++item_count_;

			if (list_ == nullptr)
			{
				list_ = new_part;
			}
			else
			{
				end_->next = new_part;
			}

			end_ = new_part;
		}
		virtual void AddOrdered(T new_item)
		{
			Node* new_part = new Node(new_item);

			++item_count_;

			if (list_ == nullptr)
			{
				list_ = new_part;
				end_ = new_part;

				return;
			}

			if (new_item < list_->item)
			{
				new_part->next = list_;
				list_ = new_part;

				return;
			}

			Node* temp = list_;

			while (temp->next != nullptr)
			{
				if (temp->item <= new_item && new_item <= temp->next->item)
				{
					new_part->next = temp->next;
					temp->next = new_part;

					return;
				}

				temp = temp->next;
			}

			temp->next = new_part;
			end_ = new_part;
		}
		virtual void Reverse()
		{
			if (list_ == nullptr)
			{
				return;
			}

			Node* start_backup = list_;

			Node* t;
			Node* a = nullptr;
			Node* x;

			Node* temp = list_;

			while (true)
			{
				t = temp->next;
				temp->next = a;
				a = t;
				x = temp;

				temp = t->next;
				t->next = x;

				if (temp == nullptr)
				{
					list_ = t;
					return;
				}

				if (temp->next == nullptr)
				{
					temp->next = t;
					list_ = temp;

					return;
				}
			}

			end_ = start_backup;
		}
		virtual void Print() const
		{
			if (list_ == nullptr)
			{
				return;
			}

			Node* temp = list_;

			do
			{
				std::cout << temp << '\t' << temp->item << '\t' << temp->next << '\n';
				temp = temp->next;
			}
			while (temp != nullptr);

			std::cout << '\n';
		}


	protected:
		struct Node
		{
			Node* next = nullptr;

			T item;

			Node(T new_item)
				:
				item( new_item )
			{

			}
		};


	protected:
		Node* list_ = nullptr;
		Node* end_  = nullptr;

		size_t item_count_ = static_cast<size_t>(0);


	private:
	};
}
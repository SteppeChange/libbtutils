#ifndef __SMART_PTR_H__
#define __SMART_PTR_H__

template <typename Interface>
class smart_ptr
{
	typedef void (smart_ptr::*bool_type)() const;
	void this_type_does_not_support_comparisons() const {}
public:
	smart_ptr() {
		ptr = NULL;
	}
	smart_ptr(const smart_ptr& com) {
		ptr = com.get();
		if (ptr) ptr->AddRef();
	}
	explicit smart_ptr(Interface* p) {
		ptr = p;
		if (ptr) {
			ptr->AddRef();
		}
	}
	~smart_ptr() {
		if (ptr) {
			ptr->Release();
		}
	}

	smart_ptr & operator=(smart_ptr const & r) {
		if(ptr != r.ptr) {
			if(r.ptr) r.ptr->AddRef();
			if(ptr) ptr->Release();
			ptr = r.ptr;
		}
		return *this;
	}

	smart_ptr & operator=(Interface* p) {
		if(ptr != p) {
			if(p) p->AddRef();
			if(ptr) ptr->Release();
			ptr = p;
		}
		return *this;
	}

	template<class Y> smart_ptr & operator=(smart_ptr<Y> const & r) {
		if(ptr != r.ptr) {
			if(r.ptr) r.ptr->AddRef();
			if(ptr) ptr->Release();
			ptr = r.ptr;
		}
		return *this;
	}

	template<class Y> smart_ptr(smart_ptr<Y> const & r) {
		ptr = r.get();
		if(ptr) ptr->AddRef();
	}

	Interface* operator->() const { return ptr; }
	bool operator==(smart_ptr<Interface> const& c) const { return c.ptr == ptr; }
	bool operator==(Interface* p) const { return p == ptr; }
	bool operator!=(smart_ptr<Interface> const& c) const { return c.ptr != ptr; }
	bool operator!=(Interface* p) const { return p != ptr; }
	bool operator <(smart_ptr<Interface> const &c) const { return ptr < c.ptr; }
	//purely here for convention's sake
	Interface* get() const { return ptr; }

	// assert that ptr is NULL since this is likely passed in to
	// QueryInterface for it to be filled in
	Interface** operator&() const
	{ assert(ptr == NULL); return (Interface**)&ptr; }

	void reset(Interface* p = NULL)
	{
		if (ptr) ptr->Release();
		ptr = p;
		if (ptr) ptr->AddRef();
	}

	void swap(smart_ptr& p) {
		Interface* t = p.ptr;
		p.ptr = ptr;
		ptr = t;
	}
	operator bool_type() const {
		return ptr ? &smart_ptr::this_type_does_not_support_comparisons : 0;
	}

	Interface& operator*() { return *ptr; }
	Interface const& operator*() const { return *ptr; }

protected:
	Interface* ptr;
};


#endif

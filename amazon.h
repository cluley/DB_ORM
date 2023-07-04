#pragma once

#include <iostream>
#include <wt/Dbo/Dbo.h>
#include <Wt/Dbo/backend/Postgres.h>

class book;

class publisher {
public:
	std::string name = "";
	Wt::Dbo::collection < Wt::Dbo::ptr<book>> books;

	template<class Action>
	void persist(Action& a)
	{
		Wt::Dbo::field(a, name, "name");
		Wt::Dbo::hasMany(a, books, Wt::Dbo::ManyToOne, "publisher");
	}
};

class stock;

class book {
public:
	std::string title = "";
	Wt::Dbo::ptr<publisher> publisher;
	Wt::Dbo::collection < Wt::Dbo::ptr<stock>> stocks;

	template<class Action>
	void persist(Action& a)
	{
		Wt::Dbo::field(a, title, "title");
		Wt::Dbo::belongsTo(a, publisher, "publisher");
		Wt::Dbo::hasMany(a, stocks, Wt::Dbo::ManyToOne, "book");
	}
};

class shop {
public:
	std::string name = "";
	Wt::Dbo::collection < Wt::Dbo::ptr<stock>> stocks;

	template<class Action>
	void persist(Action& a)
	{
		Wt::Dbo::field(a, name, "name");
		Wt::Dbo::hasMany(a, stocks, Wt::Dbo::ManyToOne, "shop");
	}
};

class sale;

class stock {
public:
	Wt::Dbo::ptr<book> book;
	Wt::Dbo::ptr<shop> shop;
	int count = 0;
	Wt::Dbo::collection < Wt::Dbo::ptr<sale>> sales;

	template<class Action>
	void persist(Action& a)
	{
		Wt::Dbo::field(a, count, "count");
		Wt::Dbo::belongsTo(a, book, "book");
		Wt::Dbo::belongsTo(a, shop, "shop");
		Wt::Dbo::hasMany(a, sales, Wt::Dbo::ManyToOne, "stock");
	}
};

class sale {
public:
	double price = 0.0;
	std::string date = "";
	Wt::Dbo::ptr<stock> stock;
	int count = 0;

	template<class Action>
	void persist(Action& a)
	{
		Wt::Dbo::field(a, price, "price");
		Wt::Dbo::field(a, date, "date_sale");
		Wt::Dbo::belongsTo(a, stock, "stock");
		Wt::Dbo::field(a, count, "count");
	}
};
#include <iostream>
#include <set>

#include "amazon.h"

int main() {
	std::string url =
		"host=127.0.0.1 "
		"port=5432 "
		"dbname=XXXX "
		"user=XXXX "
		"password=XXXX";
	
	try {
		auto conn = std::make_unique<Wt::Dbo::backend::Postgres>(url);

		Wt::Dbo::Session session;
		session.setConnection(std::move(conn));
		session.mapClass<publisher>("publisher");
		session.mapClass<book>("book");
		session.mapClass<shop>("shop");
		session.mapClass<stock>("stock");
		session.mapClass<sale>("sale");

		session.createTables();

		Wt::Dbo::Transaction tx(session);

		std::unique_ptr<publisher> ecsmo(new publisher);
		ecsmo->name = "Ecsmo";
		Wt::Dbo::ptr<publisher> ecsmoPtr = session.add(std::move(ecsmo));

		std::unique_ptr<publisher> act(new publisher);
		act->name = "ACT";
		Wt::Dbo::ptr<publisher> actPtr = session.add(std::move(act));

		std::unique_ptr<publisher> alpina(new publisher);
		alpina->name = "Alpina Publisher";
		session.add(std::move(alpina));

		std::unique_ptr<book> l_Woman(new book);
		l_Woman->title = "Little Woman";
		l_Woman->publisher = ecsmoPtr;
		session.add(std::move(l_Woman));

		std::unique_ptr<book> gatsby(new book);
		gatsby->title = "The Great Gatsby";
		gatsby->publisher = ecsmoPtr;
		session.add(std::move(gatsby));

		std::unique_ptr<book> and_None(new book);
		and_None->title = "And Then There Were None";
		and_None->publisher = ecsmoPtr;
		session.add(std::move(and_None));

		std::unique_ptr<book> sherlock(new book);
		sherlock->title = "The Adventures of Sherlock Holmes";
		Wt::Dbo::ptr<book> sherlockPtr = session.add(std::move(sherlock));
		actPtr.modify()->books.insert(sherlockPtr);

		std::unique_ptr<book> prince(new book);
		prince->title = "Le petit prince";
		Wt::Dbo::ptr<book> princePtr = session.add(std::move(prince));
		actPtr.modify()->books.insert(princePtr);

		std::unique_ptr<book> lotf(new book);
		lotf->title = "Lord of the Flies";
		Wt::Dbo::ptr<book> lotfPtr = session.add(std::move(lotf));
		actPtr.modify()->books.insert(lotfPtr);

		Wt::Dbo::ptr<publisher> alpinaPtr = session.find<publisher>().where("name = ?").bind("Alpina Publisher");

		std::unique_ptr<book> p_and_p(new book);
		p_and_p->title = "Pride and Prejudice";
		p_and_p->publisher = alpinaPtr;
		session.add(std::move(p_and_p));

		std::unique_ptr<book> w_fang(new book);
		w_fang->title = "White Fang";
		w_fang->publisher = alpinaPtr;
		session.add(std::move(w_fang));

		std::unique_ptr<book> farm(new book);
		farm->title = "Animal Farm";
		farm->publisher = alpinaPtr;
		session.add(std::move(farm));

		std::unique_ptr<shop> labyrinth(new shop);
		labyrinth->name = "Лабиринт";
		Wt::Dbo::ptr<shop> labyrinthPtr = session.add(std::move(labyrinth));

		std::unique_ptr<shop> r_city(new shop);
		r_city->name = "Читай-город";
		Wt::Dbo::ptr<shop> r_cityPtr = session.add(std::move(r_city));

		std::unique_ptr<shop> book24(new shop);
		book24->name = "Book24";
		Wt::Dbo::ptr<shop> book24Ptr = session.add(std::move(book24));

		Wt::Dbo::ptr<book> l_WomanPtr = session.find<book>().where("title = ?").bind("Little Woman");
		Wt::Dbo::ptr<book> gatsbyPtr = session.find<book>().where("title = ?").bind("The Great Gatsby");
		Wt::Dbo::ptr<book> and_NonePtr = session.find<book>().where("title = ?").bind("And Then There Were None");
		Wt::Dbo::ptr<book> p_and_pPtr = session.find<book>().where("title = ?").bind("Pride and Prejudice");
		Wt::Dbo::ptr<book> w_fangPtr = session.find<book>().where("title = ?").bind("White Fang");
		Wt::Dbo::ptr<book> farmPtr = session.find<book>().where("title = ?").bind("Animal Farm");

		std::unique_ptr<stock> stock№1(new stock);
		stock№1->book = l_WomanPtr;
		stock№1->count = 55;
		stock№1->shop = labyrinthPtr;
		Wt::Dbo::ptr<stock> stock№1Ptr = session.add(std::move(stock№1));

		std::unique_ptr<stock> stock№2(new stock);
		stock№2->book = gatsbyPtr;
		stock№2->count = 23;
		stock№2->shop = labyrinthPtr;
		Wt::Dbo::ptr<stock> stock№2Ptr = session.add(std::move(stock№2));

		std::unique_ptr<stock> stock№3(new stock);
		stock№3->book = and_NonePtr;
		stock№3->count = 71;
		stock№3->shop = labyrinthPtr;
		Wt::Dbo::ptr<stock> stock№3Ptr = session.add(std::move(stock№3));

		std::unique_ptr<stock> stock№4(new stock);
		stock№4->book = sherlockPtr;
		stock№4->count = 166;
		stock№4->shop = book24Ptr;
		Wt::Dbo::ptr<stock> stock№4Ptr = session.add(std::move(stock№4));

		std::unique_ptr<stock> stock№5(new stock);
		stock№5->book = princePtr;
		stock№5->count = 10;
		stock№5->shop = r_cityPtr;
		Wt::Dbo::ptr<stock> stock№5Ptr = session.add(std::move(stock№5));

		std::unique_ptr<stock> stock№6(new stock);
		stock№6->book = lotfPtr;
		stock№6->count = 49;
		stock№6->shop = book24Ptr;
		Wt::Dbo::ptr<stock> stock№6Ptr = session.add(std::move(stock№6));

		std::unique_ptr<stock> stock№7(new stock);
		stock№7->book = p_and_pPtr;
		stock№7->count = 33;
		stock№7->shop = r_cityPtr;
		Wt::Dbo::ptr<stock> stock№7Ptr = session.add(std::move(stock№7));

		std::unique_ptr<stock> stock№8(new stock);
		stock№8->book = w_fangPtr;
		stock№8->count = 115;
		stock№8->shop = r_cityPtr;
		Wt::Dbo::ptr<stock> stock№8Ptr = session.add(std::move(stock№8));

		std::unique_ptr<stock> stock№9(new stock);
		stock№9->book = farmPtr;
		stock№9->count = 61;
		stock№9->shop = r_cityPtr;
		Wt::Dbo::ptr<stock> stock№9Ptr = session.add(std::move(stock№9));

		std::unique_ptr<sale> sale№1(new sale);
		sale№1->price = 3.99;
		sale№1->date = "06.06.2023";
		sale№1->stock = stock№5Ptr;
		sale№1->count = 7;
		session.add(std::move(sale№1));

		std::unique_ptr<sale> sale№2(new sale);
		sale№2->price = 4.99;
		sale№2->date = "23.06.2023";
		sale№2->stock = stock№1Ptr;
		sale№2->count = 22;
		session.add(std::move(sale№2));

		std::unique_ptr<sale> sale№3(new sale);
		sale№3->price = 2.49;
		sale№3->date = "01.02.2023";
		sale№3->stock = stock№9Ptr;
		sale№3->count = 37;
		session.add(std::move(sale№3));

		std::unique_ptr<sale> sale№4(new sale);
		sale№4->price = 5.49;
		sale№4->date = "12.04.2023";
		sale№4->stock = stock№3Ptr;
		sale№4->count = 3;
		session.add(std::move(sale№4));

		std::unique_ptr<sale> sale№5(new sale);
		sale№5->price = 3.0;
		sale№5->date = "14.05.2023";
		sale№5->stock = stock№8Ptr;
		sale№5->count = 10;
		session.add(std::move(sale№5));

		std::unique_ptr<sale> sale№6(new sale);
		sale№6->price = 2.99;
		sale№6->date = "29.01.2023";
		sale№6->stock = stock№4Ptr;
		sale№6->count = 56;
		session.add(std::move(sale№6));

		std::unique_ptr<sale> sale№7(new sale);
		sale№7->price = 1.99;
		sale№7->date = "30.05.2023";
		sale№7->stock = stock№7Ptr;
		sale№7->count = 31;
		session.add(std::move(sale№7));

		std::unique_ptr<sale> sale№8(new sale);
		sale№8->price = 3.49;
		sale№8->date = "17.02.2023";
		sale№8->stock = stock№6Ptr;
		sale№8->count = 14;
		session.add(std::move(sale№8));

		std::unique_ptr<sale> sale№9(new sale);
		sale№9->price = 2.0;
		sale№9->date = "08.03.2023";
		sale№9->stock = stock№2Ptr;
		sale№9->count = 1;
		session.add(std::move(sale№9));

		tx.commit();
	}
	catch (const Wt::Dbo::Exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	try
	{
		auto conn = std::make_unique<Wt::Dbo::backend::Postgres>(url);
		Wt::Dbo::Session session;
		session.setConnection(std::move(conn));
		session.mapClass<publisher>("publisher");
		session.mapClass<book>("book");
		session.mapClass<shop>("shop");
		session.mapClass<stock>("stock");
		session.mapClass<sale>("sale");
		Wt::Dbo::Transaction tx(session);

		std::string input = "";
		std::cout << "Введите издателя: ";
		std::getline(std::cin, input);

		int pub_id = session.query<int>("SELECT id FROM publisher").where("name = ?").bind(input);

		using Books = Wt::Dbo::collection<Wt::Dbo::ptr<book>>;
		Books books = session.find<book>().where("publisher_id = ?").bind(pub_id);

		std::set<std::string> shops;

		for (const Wt::Dbo::ptr<book>& book : books)
		{
			for (const Wt::Dbo::ptr<stock>& stock : book->stocks)
			{
				shops.emplace(session.query<std::string>("SELECT name FROM shop").where("id = ?").bind(stock->shop));
			}
		}

		std::cout << input << " bookstores:\n";
		for (const auto& shop : shops)
		{
			std::cout << shop << std::endl;
		}

		tx.commit();
	}
	catch (const Wt::Dbo::Exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}
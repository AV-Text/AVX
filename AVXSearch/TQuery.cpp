///////////////////////////////////////////////////////////
//  TQuery.cpp
//  Implementation of the Class TQuery
//  Created on:      29-Nov-2023 11:27:01 PM
//  Original author: Me
///////////////////////////////////////////////////////////

#include <TQuery.h>
#include <TBook.h>
#include <TExpression.h>
#include <AVXFind.h>

#include <Serialization.h>

TQuery::TQuery(AVXBlueprint& blueprint): blueprint(blueprint), query_id(uint64(this)), settings(blueprint.settings)
{
	this->book_cnt = 0;
	this->book_hits = 0;
	this->chapter_hits = 0;
	this->verse_hits = 0;
	this->total_hits = 0;
	this->error_code = 0;

	uint16 idx = 0;
	for (AVXFind* avx : this->blueprint.searches)
	{
		this->expressions.push_back(new TExpression(*avx, idx++));
	}
	this->search();
}

TQuery::~TQuery()
{
	for (auto expression : this->expressions)
	{
		delete expression;
	}
	for (auto book = this->books.begin(); book != this->books.end(); book++)
	{
		delete book->second;
	}
}

std::string TQuery::fetch(byte book_num, byte chapter_num)
{
	if (book_num >= 1 && book_num <= 66)
	{
		auto b = book_num - 1;

		if (this->books[b] != nullptr)
		{
			TBook& book = *(this->books[b]);

			auto result = book.fetch(chapter_num);

			return result;
		}
	}
	return "";
}

bool TQuery::add_scope(uint32 spec)
{
	byte book = spec >> 24;

	if (book == 0)
	{
		for (byte num = 1; num <= 66; num++)
		{
			this->books[num] = new TBook(num);
		}
		this->book_cnt = 66;
		return true;
	}
	else if (book >= 1 && book <= 66)
	{
		if (books.find(book) == this->books.end())
		{
			this->books[book] = new TBook(book);
		}
		this->book_cnt = byte(this->books.size());
		return true;
	}
	return false;
}

bool TQuery::search()
{
	if (this->book_cnt == 0)
		this->add_scope(0);

	int cnt = 0;
	int ok = true;
	for (auto bk = this->books.begin(); bk != this->books.end(); ++bk)
	{
		TBook* book = bk->second;

		for (auto expression : this->expressions)
		{
			cnt++;
			ok = book->search(*expression, this->settings, this->scope); // TODO: update hits attributes in TQuery
			if (!ok)
				return false;
		}
	}
	return (cnt > 0);
}

std::string TQuery::serialize()
{
	rapidjson::StringBuffer sb;
	rapidjson::PrettyWriter<rapidjson::StringBuffer> builder(sb);

	builder.StartObject();

	builder.Key("book_cnt");
	builder.Uint64(this->book_cnt); // get this value from scope

	builder.Key("book_hits");
	builder.Uint64(this->book_hits);

	builder.Key("chapter_hits");
	builder.Uint64(this->chapter_hits);

	builder.Key("error_code");
	builder.Uint(this->error_code);

	builder.Key("query_id");
	builder.Uint64(this->query_id);

	builder.Key("total_hits");
	builder.Uint64(this->total_hits);

	builder.Key("verse_hits");
	builder.Uint64(this->verse_hits);

	builder.Key("scope");
	builder.StartArray();
	for (uint32 item : this->scope)
		builder.Uint(item);
	builder.EndArray();

	this->settings.build(builder);

	builder.Key("expressions");
	builder.StartArray();
	for (TExpression* expression : this->expressions)
	{
		expression->build(builder);
	}
	builder.EndArray();

	builder.Key("books");
	builder.StartArray();
	for (auto bk = this->books.begin(); bk != this->books.end(); ++bk)
	{
		TBook* book = bk->second;
		book->build(builder);
	}
	builder.EndArray();

	builder.EndObject();

	return sb.GetString();
}
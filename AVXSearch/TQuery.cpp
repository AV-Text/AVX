///////////////////////////////////////////////////////////
//  TQuery.cpp
//  Implementation of the Class TQuery
//  Created on:      29-Nov-2023 11:27:01 PM
//  Original author: Me
///////////////////////////////////////////////////////////

#include <TQuery.h>
#include "TBook.h"
#include "TExpression.h"

#include <Serialization.h>

TQuery::TQuery(AVXBlueprint* blueprint)
{
	this->blueprint = blueprint;
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
	byte book = spec >> 16;

	if (book == 0)
	{
		for (byte idx = 0; idx < 66; idx++)
		{
			this->books[idx] = new TBook(idx+1);
		}
	}
	else if (book >= 1 && book <= 66)
	{
		byte idx = book - 1;

		if (this->books[idx] == nullptr)
		{
			this->books[idx] = new TBook(book);
		}
		return true;
	}
	return false;
}

bool TQuery::search()
{
	for (auto bk = this->books.begin(); bk != this->books.end(); ++bk)
	{
		TBook* book = bk->second;

		for (auto expression : this->expressions)
		{
			book->search(*expression, this->settings, this->scope); // TODO: update hits attributes in TQuery
		}
	}
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
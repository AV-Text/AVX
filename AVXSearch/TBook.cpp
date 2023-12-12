///////////////////////////////////////////////////////////
//  TBook.cpp
//  Implementation of the Class TBook
//  Created on:      29-Nov-2023 11:27:00 PM
//  Original author: Me
///////////////////////////////////////////////////////////

#include <TBook.h>
#include <TChapter.h>

#include <book.h>

#include <map>
#include <vector>

TBook::TBook(byte num)
{
	this->book_num = (num >= 1 && num <= 66) ? num : 0;

	// TO DO (TODO): call AVXText to fill other properties
}

TBook::~TBook()
{

}

bool TBook::search(TExpression& expression, TSettings& settings, std::vector<uint32> scope)
{
	return expression.expression_avx.quoted
		? search_quoted(expression, settings, scope)
		: search_unquoted(expression, settings, scope);
}

bool TBook::search_quoted(TExpression& expression, TSettings& settings, std::vector<uint32> scope)
{
    auto frag_cnt = expression.fragments.size();

    if (frag_cnt < 1)
        return false;

    bool hit = false;
    auto book = AVXBook::GetBook(this->book_num);

    auto writ = book.getWrit();

    uint32 w;

    if (settings.span > 0)
    {
        uint32 len = 0;
        for (w = 0; w < book.writ_cnt; w++, writ++)
        {
            if (len == 0)
            {
                len = w + settings.span;
                if (len > book.writ_cnt)
                    len = book.writ_cnt;
            } 
            uint32 wi = w;
            auto spanwrit = writ + 1;

            for (TFragment* fragment : expression.fragments)
            {
                auto all_of_remaining = fragment->all_of.size();

                for (auto options : fragment->all_of)
                {
                    --all_of_remaining;

                    auto match = new TMatch(expression, *fragment);
                    for (auto feature : options->any_of)
                    {
                        auto coord = (uint32(this->book_num) << 24) | (uint32(spanwrit->b) << 16) | (uint32(spanwrit->v) << 8) | uint32(spanwrit->wc);
                        auto tag = new TTag(*options, *feature, coord);
                        if (wi > len)
                            break;

                        if (feature->feature_avx.compare(*spanwrit, *match, *tag) && (all_of_remaining == 0))
                        {
                            for (auto t : match->highlights)
                            {
                                byte c = 0;
                                if (match->start == 0)
                                {
                                    match->start = t->coordinates;
                                    c = t->get_chapter();
                                }
                                else if (match->start > t->coordinates)
                                    match->start = t->coordinates;

                                else if (match->until < t->coordinates)
                                    match->until = t->coordinates;

                                this->total_hits++;

                                TChapter* chapter = this->chapters[c];
                                if (chapter == nullptr)
                                {
                                    chapter = new TChapter(c);
                                    this->chapters[c] = chapter;
                                }
                                chapter->total_hits++;
                                this->total_hits++;
                            }
                        }
                        else
                        {
                            if (fragment->anchored)
                            {
                                delete match;
                                delete tag;
                                goto NOT_FOUND_1;
                            }
                            if (wi == len - 1) // end-of-verse with verse-span granularity
                            {
                                delete match;
                                delete tag;
                                goto NOT_FOUND_1;
                            }
                        }
                        wi++;
                        spanwrit++;
                    }
                }
            }
        NOT_FOUND_1:
            continue;
        }
    }
    else // almost the same as the previous if condition, but dynamic verse-span instead of fixed-length-span
    {
        for (w = 0; w < book.writ_cnt; w++, writ += writ->wc)
        {
            auto spanwrit = writ + 1;

            for (TFragment* fragment : expression.fragments)
            {
                auto all_of_remaining = fragment->all_of.size();

                for (auto options : fragment->all_of)
                {
                    --all_of_remaining;

                    auto match = new TMatch(expression, *fragment);
                    for (auto feature : options->any_of)
                    {
                        auto coord = (uint32(this->book_num) << 24) | (uint32(spanwrit->b) << 16) | (uint32(spanwrit->v) << 8) | uint32(spanwrit->wc);
                        auto tag = new TTag(*options, *feature, coord);

                        if (feature->feature_avx.compare(*spanwrit, *match, *tag) && (all_of_remaining == 0))
                        {
                            for (auto t : match->highlights)
                            {
                                byte c = 0;
                                if (match->start == 0)
                                {
                                    match->start = t->coordinates;
                                    c = t->get_chapter();
                                }
                                else if (match->start > t->coordinates)
                                    match->start = t->coordinates;

                                else if (match->until < t->coordinates)
                                    match->until = t->coordinates;

                                this->total_hits++;

                                TChapter* chapter = this->chapters[c];
                                if (chapter == nullptr)
                                {
                                    chapter = new TChapter(c);
                                    this->chapters[c] = chapter;
                                }
                                chapter->total_hits++;
                                this->total_hits++;
                            }
                        }
                        else
                        {
                            if (fragment->anchored)
                            {
                                delete match;
                                delete tag;
                                goto NOT_FOUND_2;
                            }
                        }
                        spanwrit++;
                    }
                }
            }
        NOT_FOUND_2:
            continue;
        }
    }
    return hit;
}
bool TBook::search_unquoted(TExpression& expression, TSettings& settings, std::vector<uint32> scope)
{
    auto frag_cnt = expression.fragments.size();

    if (frag_cnt < 1)
        return false;

    bool found = false;

    auto book = AVXBook::GetBook(this->book_num);

    auto writ = book.getWrit();
    auto until = writ + book.writ_cnt - 1;

    for (/**/; writ <= until; /**/)
    {
        uint16 span = settings.span > 0 ? settings.span : writ->wc;
        if (writ + span - 1 > until)
            span = (uint16)(until - writ);

        std::map<uint64, bool> matched;
        for (uint32 wi = 0; wi < span; wi++)
        {
            const WrittenContent& spanwrit = writ[wi];

            matched.clear();
            found = false;

            // TO DO: memory management :: LOTS OF LEAKS HERE !!!
            for (auto fragment : expression.fragments)
            {
                byte c = 0;
                for (auto options : fragment->all_of)
                {
                    auto option_key = uint64(options);

                    auto match = new TMatch(expression, *fragment);
                    for (auto feature : options->any_of)
                    {
                        auto coord = (uint32(this->book_num) << 24) | (uint32(spanwrit.c) << 16) | (uint32(spanwrit.v) << 8) | uint32(spanwrit.wc);
                        auto tag = new TTag(*options, *feature, coord);

                        if (feature->feature_avx.compare(spanwrit, *match, *tag))
                        {
                            matched[option_key] = true;
                            if (c == 0)
                                c = spanwrit.c;

                            if (fragment->all_of.size() == matched.size())
                            {
                                bool exists = (this->chapters.find(c) == this->chapters.end());
                                auto chapter = exists ? this->chapters[c] : new TChapter(c);
                                chapter->matches.push_back(match);
                                if (!exists)
                                    this->chapters[c] = chapter;
                            }
                            break;
                        }
                    }
                }
            }
        }
        if (settings.span == 0) // verse granularity
        {
            writ += span;
        }
        else
        {
            writ++;
        }
    }
    return found;
}

std::string TBook::fetch(byte chapter_num)
{
	auto chapter = this->chapters.find(chapter_num);

	return chapter != this->chapters.end() ? chapter->second->serialize() : "";
}

void TBook::build(rapidjson::Writer<rapidjson::StringBuffer>& builder)
{
	builder.StartObject();

	builder.Key("book_num");
	builder.Uint(this->book_num); // get this value from scope

	builder.Key("book_hits");
	builder.Uint64(this->book_hits);

	builder.Key("chapter_cnt");
	builder.Uint64(this->chapter_cnt);

	builder.Key("chapter_hits");
	builder.Uint64(this->chapter_hits);

	builder.Key("total_hits");
	builder.Uint64(this->total_hits);

	builder.Key("verse_hits");
	builder.Uint64(this->verse_hits);

	builder.Key("verse_hits_by_chapter");
	builder.StartArray();
	for (auto hits = this->verse_hits_by_chapter.begin(); hits != this->verse_hits_by_chapter.end(); ++hits)
	{
		byte chapter_num = hits->first;
		uint64 cnt = hits->second;

		builder.StartObject();
		builder.Key("chapter_num");
		builder.Uint(chapter_num);
		builder.Key("verse_hits");
		builder.Uint64(cnt);
		builder.EndObject();
	}
	builder.EndArray();

	builder.EndObject();
}

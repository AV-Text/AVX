///////////////////////////////////////////////////////////
//  TBook.cpp
//  Implementation of the Class TBook
//  Created on:      29-Nov-2023 11:27:00 PM
//  Original author: Me
///////////////////////////////////////////////////////////

#include <TBook.h>
#include <map>
#include <book.h>

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
            std::map<uint32, std::tuple<const char*, const uint16>> matched;
            bool found = false; // obsolete from AVXFound: this->requirements[0]->compare(*writ, matched);
            if (found)
            {
                uint32 wi = w;
                auto spanwrit = writ + 1;

                for (const TFragment* fragment : expression.fragments)
                {
/*                  for (AVXMatchAny* req : fragment->requirements)
                    {
                        if (wi > len)
                            break;

                        if (!req->compare(*spanwrit, matched))
                        {
                            if (fragment->anchored)
                                goto NOT_FOUND_1;
                            if (wi == len - 1) // end-of-verse with verse-span granularity
                                goto NOT_FOUND_1;
                        }
                        wi++;
                        spanwrit++;
                    }*/
                }
                /*
                hit = true;
                auto found = new TMatch();
                for (auto const& [coord, pair] : matched)
                {
                    const char* frag = std::get<0>(pair);
                    const char* feat = std::get<0>(pair);
                    auto match = new TTag(uint32(coord), feat);
                    found->add(match);
                }*/
                //this->results.founds.push_back(found);
            }
        NOT_FOUND_1:
            continue;
        }
    }
    else
    {
        uint32 len = writ->wc;
        for (w = 0; w < book.writ_cnt; w += len, writ += len)
        {
            std::map<uint32, std::tuple<const char*, const uint16>> matched;
            bool found = false; // this->requirements[0]->compare(*writ, matched);
            if (found)
            {
                uint32 wi = w;
                uint32 wi_len = wi + len;

                auto spanwrit = writ + 1;

                for (auto fragment : expression.fragments)
                {
/*                  for (auto req : fragment->requirements)
                    {
                        if (!req->compare(*spanwrit, matched))
                        {
                            if (fragment->anchored)
                                goto NOT_FOUND_2;
                            if (wi == wi_len - 1) // end-of-verse with verse-span granularity
                                goto NOT_FOUND_2;
                        }
                    }*/
                }
                hit = true;
                //auto found = new TMatch();
                for (auto const& [coord, pair] : matched)
                {
                    const char* frag = std::get<0>(pair);
                    const char* feat = std::get<0>(pair);
                    //auto match = new TTag(uint32(coord), feat);
                    //found->add(match);
                }
                //this->results.founds.push_back(found);
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
    uint32 hit_cnt = 0;

    auto writ = book.getWrit();
    auto until = writ + book.writ_cnt - 1;

    for (/**/; writ <= until; /**/)
    {
        uint32 cnt = 0;

        uint16 span = settings.span > 0 ? settings.span : writ->wc;
        if (writ + span - 1 > until)
            span = (uint16)(until - writ);

        for (uint32 wi = 0; wi < span; wi++)
        {
            std::map<uint32, std::tuple<const char*, const uint16>> matched;
            found = false;

            for (auto frag : expression.fragments)
            {
                bool hit = false; //  frag->compare(writ[wi], matched);
                if (hit)
                {
                    cnt++;
                    //hits[s] = true;
                }
                else break;
            }
            if (cnt >= frag_cnt)
            {
                uint32 hit_cnt = 0;
                //for (uint32 s = 0; s < frag_cnt; s++)
                    //if (hits[s])
                        //hit_cnt++;

                if (hit_cnt == frag_cnt)
                {
                    found = true;/*
                    auto foundMatch = new TMatch();
                    for (auto const& [coord, pair] : matched)
                    {
                        const char* frag = std::get<0>(pair);
                        const char* feat = std::get<0>(pair);
                        auto match = new TTag(uint32(coord), feat);
                        foundMatch->add(match);
                    }*/
                    //this->results.founds.push_back(foundMatch);
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

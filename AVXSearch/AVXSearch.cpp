#include "AVXSearch.h"
#include "AVXSegment.h"
#include "AVXResults.h"
#include <map>

static std::unordered_set<uintptr_t> MemoryTable;
/*
static uint32 Find(AVXSearch& search, AVXResults& results)
{
    auto books = AVXBookIndex::index;
    auto chapters = AVXChapterIndex::index;

    for (uint8 b = 1; b <= 66; b++)
    {
        auto book = books + b;
        auto chap = chapters + book->chapter_idx;
        auto writ = AVXWritten::getWrit(b);
        uint8 c = 1;
        uint8 v = 1;

        for (uint32 w = 0; w < book->writ_cnt; w++, writ++)
        {
            for (int f  = 0; f < search.; f++)
            {
                auto find = request.search[f];
            for (auto find : request.sea)
            {

        foreach(var clause in vector.Searches)
        {
            foreach(var segment in clause.Segments)
            {
                int frags = 0;

                foreach(var fragment in segment.Fragments) // and'ed
                {
                    bool hit = false;
                    foreach(var feature in fragment.Features) // or'ed
                    {
                        var ftype = feature.GetType();
                        if (ftype == typeof(QWord))
                        {
                            hit = (writ.WordKey & 0x3FFF) == (uint)((QWord)feature).WordKeys[0];    // todo: wordkeys is now multi-valued
                        }
                        else if (ftype == typeof(QLemma))
                        {
                            foreach(var lemma in((QLemma)feature).Lemmata)
                            {
                                hit = writ.Lemma == lemma;
                                if (hit)
                                    break;
                            }
                        }
                        else if (ftype == typeof(QPartOfSpeech))
                        {
                            var fpos = ((QPartOfSpeech)feature);

                            if (fpos.Pos32 != 0)
                                hit = writ.POS32 == fpos.Pos32;
                            else if (fpos.PnPos12 != 0)
                                hit = (writ.pnPOS12 & fpos.PnPos12) == fpos.PnPos12;
                            if (fpos.Negate)
                                hit = !hit;
                            if (hit)
                                break;
                        }
                    }
                    if (!hit)
                        break;
                    frags++;
                }
                if (frags == segment.Fragments.Count)
                    yield return (writ.BCVWc.B, writ.BCVWc.C, writ.BCVWc.V, writ.BCVWc.WC, 1);
            }
        }
    }
}


static void ProcessSearch(QImplicitCommands vector)
{
	foreach(var record in Find(vector))
	{
		var book = AVX.Mem.Book.Slice((int)record.b, 1).Span[0];
		Console.WriteLine(book.name + " " + record.c.ToString() + ":" + record.v.ToString());
	}
}
*/

bool AVXSearch::search_quoted()
{
    return false;
}
bool AVXSearch::search_unquoted()
{
    auto books = AVXBookIndex::index;
    auto chapters = AVXChapterIndex::index;

    uint32 seg_cnt = 0;
    if (this->segments = nullptr)
        return false;
    for (/**/; this->segments[seg_cnt]; seg_cnt++)
        ;

    bool found = false;
    bool *hits = new bool[seg_cnt];
    for (uint8 b = 1; b <= 66; b++)
    {
        uint32 hit_cnt = 0;

        auto book = books + b;
        auto chap = chapters + book->chapter_idx;
        const AVXWritten::AVXWrit* writ = AVXWritten::getWrit(b);
        uint8 c = 1;
        uint8 v = 1;

        for (uint32 w = 0; w < book->writ_cnt; w++)
        {
            auto spanwrit = const_cast<AVXWritten::AVXWrit*>(writ);
            uint32 cnt = 0;
            for (uint32 i = 0; i < seg_cnt; i++)
                hits[i] = false;
            uint32 until = w + this->settings.span > 0 ? this->settings.span - 1 : writ->wc - 1;
            for (uint32 wi = w; wi <= until; wi++, spanwrit++)
            {
                bool found = this->segments[0]->compare(*spanwrit);
                for (uint32 s = 1; (!found) && (s < seg_cnt); s++)
                {
                    found = this->segments[s]->compare(*spanwrit);
                    if (found)
                    {
                        cnt++;
                        hits[s] = true;
                    }
                    else break;
                }
            }
            if (cnt >= seg_cnt)
            {
                uint32 hit_cnt = 0;
                for (uint32 i = 0; i < seg_cnt; i++)
                    hit_cnt++;

                if (hit_cnt == seg_cnt)
                {
                    found = true;
                    // TO DO:
                    // add result
                }
            }
        }
    }
    delete[] hits;
    return found;
}
void AVXSearch::add_scope(const AVXScope* scope)
{
    this->scopes.push_back(scope);
}

AVXSearch::AVXSearch(const XSearch* xsearch, AVXResults& results, const AVXSettings& xsettings):
    spec(xsearch->search()->c_str()),
    negate(this->xsearch->negate()),
    quoted(this->xsearch->quoted()),
    xsearch(xsearch),
    settings(settings),
    results(results),
    segments(nullptr)
{
    auto xsegments = this->xsearch->segments();

    if (xsegments != nullptr)
    {
        int segments_size = xsegments->size();
        this->segments = (AVXSegment**) (std::calloc(segments_size + 1, sizeof(AVXSegment*)));
        for (int s = 0; s < segments_size; s++)
        {
            auto xsegment = (*xsegments)[s];
            if (xsegment != nullptr)
            {
                this->segments[s] = (AVXSegment*)(new AVXSegment(xsegment));

                auto xfragments = xsegment->fragments();
                if (xfragments != nullptr)
                {
                    int fragments_size = xfragments->size();
                    for (int frag = 0; frag < fragments_size; frag++)
                    {
                        auto xfragment = (*xfragments)[frag];
                        if (xfragment != nullptr)
                        {
                            auto xfeatures = xfragment->features();
                            if (xfeatures != nullptr)
                            {
                                int features_size = xfeatures->size();
                            }
                        }
                    }
                }
            }
        }
    }
}
AVXSearch::~AVXSearch()
{
    if (this->segments != nullptr)
    {
        for (int i = 0; this->segments[i] != nullptr; i++)
        {
            std::free((void*)this->segments[i]);
        }
        std::free(this->segments);
    }
}

// For use with LoadLibrary/GetProcAdress ... no header file required
extern "C" __declspec(dllexport) const uint8* const avx_create_search(const uint8* const request)
{
    AVXResults search(request);
    search.execute();
    auto results = search.build();
	if (results != nullptr)
	{
		MemoryTable.insert(reinterpret_cast<uintptr_t>(results));
	}
	return results;
}
extern "C" __declspec(dllexport) bool avx_delete_search(const uint8* const* results)
{
	auto entry = reinterpret_cast<uintptr_t>(results);
	auto memory = reinterpret_cast<char*>(entry);

	auto it = MemoryTable.find(entry);
	if (it != MemoryTable.end()) {
		MemoryTable.erase(it);
		free(memory);
		return true;
	}
	return false;
}






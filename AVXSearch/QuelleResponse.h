#pragma once
#include <avxgen.h>
#include <string>
#include <ctime>

enum ResultType
{
	UNKNOWN = 0,
	BLUEPRINT = 1,
	SEARCH_RESULTS = 2
};
struct ResultSummaryStruct
{
	uint32 hit_count;
	uint32 verse_count;
	uint32 chapter_count;
	uint32 book_count;
};
typedef ResultSummaryStruct ResultSummary;

struct QuelleHistoryStruct
{
	uint32 id;
	time_t time;
	std::string statementRaw;
	std::string statement;
	std::string summary;
};
typedef QuelleHistoryStruct QuelleHistory;

struct QuelleResponseStruct
{
	int64 stmt_id;
	uint8* buffer;
	uint32 buffer_len;
	time_t expiration;
	ResultType type;
	ResultSummary summary;
	char* rendering;
	QuelleHistory* history;
	char* effects;	// result from singleton-command
};
typedef QuelleResponseStruct QuelleResponse;

#define QUELLE_COMMAND_CACHE_SIZE 16
const int64 LEASE_DURATION = 180; // 180 seconds = 3 minutes
class CommandResponses
{
private:
	QuelleResponse cache[QUELLE_COMMAND_CACHE_SIZE];
	uint32 get_available_slot();
	time_t obtain_expiration();
public:
	bool add(const int64 id, const uint8* const buffer, const uint32 buffer_len, const ResultType type, const ResultSummary& summary);
	const QuelleResponse* const effect(const int64 id, const char* const effects); // extend lease expiration & add command effects (important for singletons)
	const QuelleResponse* const extend(const int64 id, const char* const rendering); // extend lease expiration & add rendering
	const QuelleResponse* const extend(const int64 id, const QuelleHistory* const history); // extend lease expiration & add history
	const QuelleResponse* const extend(const int64 id); // extend lease expiration
	void release(const int64 id);

	CommandResponses();
	~CommandResponses();
};


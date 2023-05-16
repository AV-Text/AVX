#include <QuelleResponse.h>
#include <limits.h>
#include <corecrt_malloc.h>

#include <ctime>

inline time_t get_current_time()
{
	time_t current;
	time(&current);

	return current;
}

time_t CommandResponses::obtain_expiration()
{
	time_t lease;
	time(&lease);
	lease += (LEASE_DURATION * 1000);

	return lease;
}

bool CommandResponses::add(const int64 id, const uint8* const buffer, const uint32 buffer_len, const ResultType type, const ResultSummary& summary)
{
	auto idx = get_available_slot();
	if (QUELLE_COMMAND_CACHE_SIZE <= idx)
		return false;

	this->cache[idx].expiration = this->obtain_expiration();
	this->cache[idx].type = type;
	this->cache[idx].summary = summary;

	if (this->cache[idx].buffer != nullptr)
	{
		free(this->cache[idx].buffer);
		this->cache[idx].buffer = nullptr;
		this->cache[idx].buffer_len = 0;

	}
	if (this->cache[idx].rendering != nullptr)
	{
		free(this->cache[idx].rendering);
		this->cache[idx].rendering = nullptr;
	}
	if (this->cache[idx].history != nullptr)
	{
		free(this->cache[idx].history);
		this->cache[idx].history = nullptr;
	}
	if (this->cache[idx].effects != nullptr)
	{
		free(this->cache[idx].effects);
		this->cache[idx].effects = nullptr;
	}
	this->cache[idx].stmt_id = id;
	this->cache[idx].buffer = const_cast<uint8*>(buffer);
	this->cache[idx].buffer_len = buffer_len;

	return true;
}

// TO DO:
// Consider freeing memory here <XOR> Add house-keeping unction that does that (garbage collection)
//
// AS IS: There are no memory-leaks, but there is the possibility of memory-creep
void CommandResponses::release(const int64 id)
{
	for (int32 i = 0; i < QUELLE_COMMAND_CACHE_SIZE; i++)
	{
		if (this->cache[i].stmt_id == id)
		{
			this->cache[i].expiration = 0;
			this->cache[i].type = ResultType::UNKNOWN;
			break;
		}
	}
}

uint32 CommandResponses::get_available_slot()
{
	int64 min = LLONG_MAX;
	uint32 idx = QUELLE_COMMAND_CACHE_SIZE;

	time_t now = get_current_time();

	for (int32 i = 0; i < QUELLE_COMMAND_CACHE_SIZE; i++)
	{
		if (now < this->cache[i].expiration)
		{
			continue;
		}
		if (this->cache[i].expiration < min)
		{
			min = this->cache[i].expiration;
			idx = i;
		}
	}
	return idx;
}

const QuelleResponse* const CommandResponses::effect(const int64 id, const char* const effects) // extend lease expiration & add effects
{
	for (int32 i = 0; i < QUELLE_COMMAND_CACHE_SIZE; i++)
	{
		if ((this->cache[i].stmt_id == id) && (this->cache[i].buffer != nullptr || this->cache[i].effects != nullptr))
		{
			if (this->cache[i].effects != nullptr)
			{
				free(this->cache[i].effects);
			}
			this->cache[i].effects = const_cast<char*>(effects);
			this->cache[i].expiration = this->obtain_expiration();
			return this->cache + i;
		}
	}
	// We support renderings without metadata
	// This makes us a better service for REST clients
	//
	ResultSummary zero = { 0, 0, 0, 0 };
	if (this->add(id, nullptr, 0, ResultType::UNKNOWN, zero))	// recursion will only ever be two-deep, never more.
	{
		return this->extend(id, effects);
	}
	return nullptr;
}

const QuelleResponse* const CommandResponses::extend(const int64 id, const char* const rendering) // extend lease expiration & add rendering
{
	for (int32 i = 0; i < QUELLE_COMMAND_CACHE_SIZE; i++)
	{
		if ((this->cache[i].stmt_id == id) && (this->cache[i].buffer != nullptr || this->cache[i].rendering != nullptr))
		{
			if (this->cache[i].rendering != nullptr)
			{
				free(this->cache[i].rendering);
			}
			this->cache[i].rendering = const_cast<char*>(rendering);
			this->cache[i].expiration = this->obtain_expiration();
			return this->cache + i;
		}
	}
	// We support renderings without metadata
	// This makes us a better service for REST clients
	//
	ResultSummary zero = { 0, 0, 0, 0 };
	if (this->add(id, nullptr, 0, ResultType::UNKNOWN, zero))	// recursion will only ever be two-deep, never more.
	{
		return this->extend(id, rendering);
	}
	return nullptr;
}

const QuelleResponse* const CommandResponses::extend(const int64 id, const QuelleHistory* const history) // extend lease expiration & add rendering
{
	for (int32 i = 0; i < QUELLE_COMMAND_CACHE_SIZE; i++)
	{
		if ((this->cache[i].stmt_id == id) && (this->cache[i].buffer != nullptr || this->cache[i].history != nullptr))
		{
			if (this->cache[i].rendering != nullptr)
			{
				free(this->cache[i].rendering);
			}
			this->cache[i].history = const_cast<QuelleHistory*>(history);
			this->cache[i].expiration = this->obtain_expiration();
			return this->cache + i;
		}
	}
	// We support renderings without metadata
	// This makes us a better service for REST clients
	//
	ResultSummary zero = { 0, 0, 0, 0 };
	if (this->add(id, nullptr, 0, ResultType::UNKNOWN, zero))	// recursion will only ever be two-deep, never more.
	{
		return this->extend(id, history);
	}
	return nullptr;
}

const QuelleResponse* const CommandResponses::extend(const int64 id) // extend lease expiration
{
	for (int32 i = 0; i < QUELLE_COMMAND_CACHE_SIZE; i++)
	{
		if (this->cache[i].stmt_id == id && (this->cache[i].buffer != nullptr || this->cache[i].rendering != nullptr))
		{
			this->cache[i].expiration = this->obtain_expiration();
			return this->cache + i;
		}
	}
	return nullptr;
}

CommandResponses::CommandResponses()
{
	for (int32 i = 0; i < QUELLE_COMMAND_CACHE_SIZE; i++)
	{
		this->cache[i].stmt_id = 0;
		this->cache[i].buffer = nullptr;
		this->cache[i].buffer_len = 0;
		this->cache[i].expiration = 0;
		this->cache[i].type = ResultType::UNKNOWN;
		this->cache[i].rendering = nullptr;
		this->cache[i].history = nullptr;
		this->cache[i].effects = nullptr;
	}
}

CommandResponses::~CommandResponses()
{
	for (int32 i = 0; i < QUELLE_COMMAND_CACHE_SIZE; i++)
	{
		if (this->cache[i].buffer != nullptr)
		{
			free(this->cache[i].buffer);
		}
		if (this->cache[i].rendering != nullptr)
		{
			free(this->cache[i].rendering);
		}
		if (this->cache[i].effects != nullptr)
		{
			free(this->cache[i].effects);
		}
		if (this->cache[i].history != nullptr)
		{
			free(this->cache[i].history);
		}
	}
}




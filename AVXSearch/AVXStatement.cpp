#include <AVXStatement.h>

#include <AVXBlueprint.h>
#include <unordered_set>
#include <unordered_set>
#include <vector>

#include <XVMem.h>

extern "C" __declspec(dllexport) uint64 create_statement(char buffer[])
{
	auto statement = new AVXStatement(buffer);
	return uint64(statement);
}

extern "C" __declspec(dllexport) void* exec_statement(uint64 context)
{
	AVXStatement& statement = *((AVXStatement*)context);	// it would be safer to have a running object table for lookup)
	if (statement.Compile())
	{

	}
	else
	{
		;
	}
	return nullptr;
}

extern "C" __declspec(dllexport) int32 free_statement(uint64 context)
{
	delete (AVXStatement*) context;	// it would be safer to have a running object table for lookup)
	return 0;
}

AVXStatement::AVXStatement(char buffer[])
{
	this->blueprint = new AVXBlueprint(buffer);
}

bool AVXStatement::Compile()
{
	/*
	bool result = false;

	if (this->blueprint != nullptr)
	{
		XBlueprint* xblue = (XBlueprint*)this->blueprint->getRequest();
		
		if (xblue->status() == XStatusEnum::XStatusEnum_OKAY && xblue->search() != nullptr)
		{
			result = blueprint->execute();
		}
		else // XStatusEnum::XStatusEnum_UNKNOWN or anything else
		{
			result = false;
		}
	}
	return result;
	*/
	return false;
}
/*
const QuelleResponse* const AVXStatement::Execute(int64 id)
{
	return nullptr;
}
*/
std::vector<std::string> AVXStatement::GetErrors(int64 id)
{
	std::vector<std::string> empty;

	return empty;
}
std::vector<std::string> AVXStatement::GetWarnings(int64 id)
{
	std::vector<std::string> empty;

	return empty;
}
const char* const AVXStatement::CreateRendering(int64 id)
{
	return nullptr;
}
std::vector<std::string> AVXStatement::GetHistory(int64 id)
{
	std::vector<std::string> empty;

	return empty;
}
std::string AVXStatement::GetEffects(int64 id)
{
	return "";
}
void AVXStatement::Release(int64 id)
{
	// this->results.release(id);
}

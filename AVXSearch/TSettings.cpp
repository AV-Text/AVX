///////////////////////////////////////////////////////////
//  TSettings.cpp
//  Implementation of the Class TSettings
//  Created on:      29-Nov-2023 11:27:01 PM
//  Original author: Me
///////////////////////////////////////////////////////////

#include "TSettings.h"
#include <AVXSettings.h>

TSettings::TSettings(const AVXSettings& avx)
	: fuzzy_lemmata(avx.enable_lemma_matching ? 1 : 0)
	, lexicon(avx.lexicon)
	, similarity(avx.similarity)
	, span(avx.span)
{
	;
}

TSettings::~TSettings()
{
	;
}

void TSettings::build(rapidjson::Writer<rapidjson::StringBuffer>& builder)
{
	builder.Key("settings");
	builder.StartObject();
	builder.Key("fuzzy_lemmata");
	builder.Bool(this->fuzzy_lemmata == 0 ? false : true);
	builder.Key("lexicon");
	builder.Uint(this->lexicon);
	builder.Key("similarity");
	builder.Uint(this->similarity);
	builder.Key("span");
	builder.Uint(this->span);
	builder.EndObject();
}
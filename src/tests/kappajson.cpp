#include "../test.h"


#include "kappa/json.cpp"
#include "kappa/utils/atonum.cpp"
#include "kappa/utils/numtoa.cpp"

extern "C" {
#include "kappa/utils/ryu/d2s.c"
}

using namespace kp;

static void GenStat(Stat& stat, const Json& v) {
    switch (v.type()) {
    case Json::Type::ARRAY:
        for (auto const& i : v.array_items())
            GenStat(stat, i);
        stat.arrayCount++;
        stat.elementCount += v.array_items().size();
        break;

    case Json::Type::OBJECT:
        for (auto const& i : v.object_items()) {
            GenStat(stat, i.second);
            stat.stringLength += i.first.size();
        }
        stat.objectCount++;
        stat.memberCount += v.object_items().size();
        stat.stringCount += v.object_items().size();
        break;

    case Json::Type::STRING: 
        stat.stringCount++;
        stat.stringLength += v.string_value().size();
        break;

    case Json::Type::NUMBER:
        stat.numberCount++;
        break;

    case Json::Type::BOOL:
        if (v.bool_value())
            stat.trueCount++;
        else
            stat.falseCount++;
        break;

    case Json::Type::NUL:
        stat.nullCount++;
        break;
    }
}

class KappaJsonParseResult : public ParseResultBase {
public:
    Json root;
};

class KappaJsonStringResult : public StringResultBase {
public:
    virtual const char* c_str() const { return s.c_str(); }

    std::string s;
};

class KappaJsonTest : public TestBase {
public:
#if TEST_INFO
    virtual const char* GetName() const { return "kappa/json (C++17)"; }
    virtual const char* GetFilename() const { return __FILE__; }
#endif
	
#if TEST_PARSE
    virtual ParseResultBase* Parse(const char* json, size_t length) const {
        (void)length;
        KappaJsonParseResult* pr = new KappaJsonParseResult;
		auto r = Json::parse(json);
        if (!r) {
            delete pr;
            return 0;
        }
        pr->root = std::move(r.value());
    	return pr;
    }
#endif

#if TEST_STRINGIFY
    virtual StringResultBase* Stringify(const ParseResultBase* parseResult) const {
        const KappaJsonParseResult* pr = static_cast<const KappaJsonParseResult*>(parseResult);
        KappaJsonStringResult* sr = new KappaJsonStringResult;
        pr->root.to_string(sr->s);
        return sr;
    }
#endif

#if TEST_STATISTICS
    virtual bool Statistics(const ParseResultBase* parseResult, Stat* stat) const {
        const KappaJsonParseResult* pr = static_cast<const KappaJsonParseResult*>(parseResult);
        memset(stat, 0, sizeof(Stat));
        GenStat(*stat, pr->root);
        return true;
    }
#endif

#if TEST_CONFORMANCE
    virtual bool ParseDouble(const char* json, double* d) const {
        auto r = Json::parse(json);
		if (!r)
			return false;
		Json root = std::move(r.value());
        if (root.is_array() && root.array_items().size() == 1 && root.array_items()[0].is_number()) {
            *d = root.array_items()[0].number_value();
            return true;
        }
        else
            return false;
    }

    virtual bool ParseString(const char* json, std::string& s) const {
        auto r = Json::parse(json);
		if (!r)
			return false;
		Json root = std::move(r.value());
        if (root.is_array() && root.array_items().size() == 1 && root.array_items()[0].is_string()) {
            s = root.array_items()[0].string_value();
            return true;
        }
        else
            return false;
    }
#endif
};

REGISTER_TEST(KappaJsonTest);

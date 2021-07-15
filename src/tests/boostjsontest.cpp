#include "../test.h"

#define BOOST_JSON_STANDALONE
#include <boost/json/src.hpp>


static void GenStat(Stat& stat, const boost::json::value& v) {
    switch (v.kind()) {
    case boost::json::kind::array:
        for (auto const& i : v.as_array())
            GenStat(stat, i);
        stat.arrayCount++;
        stat.elementCount += v.as_array().size();
        break;

    case boost::json::kind::object:
        for (auto const& i : v.as_object()) {
            GenStat(stat, i.value());
            stat.stringLength += i.key().size();
        }
        stat.objectCount++;
        stat.memberCount += v.as_object().size();
        stat.stringCount += v.as_object().size();
        break;

    case boost::json::kind::string: 
        stat.stringCount++;
        stat.stringLength += v.as_string().size();
        break;

    case boost::json::kind::int64:
    case boost::json::kind::uint64:
    case boost::json::kind::double_:
        stat.numberCount++;
        break;

    case boost::json::kind::bool_:
        if (v.as_bool())
            stat.trueCount++;
        else
            stat.falseCount++;
        break;

    case boost::json::kind::null:
        stat.nullCount++;
        break;
    }
}

class BoostJsonParseResult : public ParseResultBase {
public:
    boost::json::value root;
};

class BoostJsonStringResult : public StringResultBase {
public:
    virtual const char* c_str() const { return s.c_str(); }

    std::string s;
};

class BoostJsonTest : public TestBase {
public:
#if TEST_INFO
    virtual const char* GetName() const { return "boost.json"; }
    virtual const char* GetFilename() const { return __FILE__; }
#endif
	
#if TEST_PARSE
    virtual ParseResultBase* Parse(const char* json, size_t length) const {
        (void)length;
        auto pr = std::make_unique<BoostJsonParseResult>();

		boost::json::error_code ec;
		pr->root = boost::json::parse( json, ec );
        if ( ec )
            return nullptr;
    	return pr.release();
    }
#endif

#if TEST_STRINGIFY
    virtual StringResultBase* Stringify(const ParseResultBase* parseResult) const {
        const BoostJsonParseResult* pr = static_cast<const BoostJsonParseResult*>(parseResult);
        BoostJsonStringResult* sr = new BoostJsonStringResult;
		sr->s = boost::json::serialize( pr->root );
        return sr;
    }
#endif

#if TEST_STATISTICS
    virtual bool Statistics(const ParseResultBase* parseResult, Stat* stat) const {
        const BoostJsonParseResult* pr = static_cast<const BoostJsonParseResult*>(parseResult);
        memset(stat, 0, sizeof(Stat));
        GenStat(*stat, pr->root);
        return true;
    }
#endif

#if TEST_CONFORMANCE
    virtual bool ParseDouble(const char* json, double* d) const {
		boost::json::error_code ec;
		auto root = boost::json::parse( json, ec );
        if (not ec && root.is_array() && root.as_array().size() == 1 && root.as_array()[0].is_number()) {
            *d = root.as_array()[0].as_double();
            return true;
        }
        else
            return false;
    }

    virtual bool ParseString(const char* json, std::string& s) const {
		boost::json::error_code ec;
		auto root = boost::json::parse( json, ec );
        if ( not ec && root.is_array() && root.as_array().size() == 1 && root.as_array()[0].is_string()) {
            s = root.as_array()[0].as_string();
            return true;
        }
        else
            return false;
    }
#endif
};

REGISTER_TEST(BoostJsonTest);

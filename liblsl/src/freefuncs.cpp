#include "../include/lsl_cpp.h"
#include "version.h"
#include "resolver_impl.h"
#include <boost/chrono/system_clocks.hpp>


// === Implementation of the free-standing functions in lsl_cpp.h ===

using namespace lsl;
using std::string;
using std::vector;

/**
* Get the protocol version.
*/
LIBLSL_CPP_API int lsl::protocol_version() { return LSL_PROTOCOL_VERSION; }

/**
* Get the library version.
*/
LIBLSL_CPP_API int lsl::library_version() { return LSL_LIBRARY_VERSION; }

/**
* Implementation of the clock facility.
*/
LIBLSL_CPP_API double lsl::local_clock() { 
	return boost::chrono::nanoseconds(boost::chrono::high_resolution_clock::now().time_since_epoch()).count()/1000000000.0; 
}


/**
* Resolve all streams on the network.
* This function returns all currently available streams from any outlet on the network.
* The network is usually the subnet specified at the local router, but may also include 
* a multicast group of machines (given that the network supports it), or list of hostnames.
* These details may optionally be customized by the experimenter in a configuration file 
* (see Configuration File in the documentation).
* This is the default mechanism used by the browsing programs and the recording program.
* @param wait_time The waiting time for the operation, in seconds, to search for streams.
*				   Warning: If this is too short (<0.5s) only a subset (or none) of the 
*							outlets that are present on the network may be returned.
* @return A vector of stream info objects (excluding their desc field), any of which can 
*         subsequently be used to open an inlet. The full info can be retrieve from the inlet.
*/
LIBLSL_CPP_API std::vector<stream_info> lsl::resolve_streams(double wait_time) {
	// create a new resolver
	resolver_impl resolver;
	// build a new query
	std::ostringstream os; os << "session_id='" << api_config::get_instance()->session_id() << "'";
	// invoke it
	std::vector<stream_info_impl> tmp = resolver.resolve_oneshot(os.str(),0,wait_time);
	return std::vector<stream_info>(tmp.begin(),tmp.end());
}


/**
* Resolve all streams with a given value for a property.
* If the goal is to resolve a specific stream, this method is preferred over resolving all streams and then selecting the desired one.
* @param prop The stream_info property that should have a specific value (e.g., "name", "type", "source_id", or "desc/manufaturer").
* @param value The string value that the property should have (e.g., "EEG" as the type property).
* @param minimum Return at least this number of streams.
* @param timeout Optionally a timeout of the operation, in seconds (default: no timeout).
*				  If the timeout expires, less than the desired number of streams (possibly none) will be returned.
* @return A vector of matching stream info objects (excluding their meta-data), any of 
*         which can subsequently be used to open an inlet.
*/
LIBLSL_CPP_API std::vector<stream_info> lsl::resolve_stream(const std::string &prop, const std::string &value, int minimum, double timeout) {
	// create a new resolver
	resolver_impl resolver;
	// build a new query
	std::ostringstream os; os << "session_id='" << api_config::get_instance()->session_id() << "' and " << prop << "='" << value << "'";
	// invoke it
	std::vector<stream_info_impl> tmp = resolver.resolve_oneshot(os.str(),minimum,timeout);
	return std::vector<stream_info>(tmp.begin(),tmp.end());
}


/**
* Resolve all streams that match a given predicate.
* Advanced query that allows to impose more conditions on the retrieved streams; the given string is an XPath 1.0 
* predicate for the <info> node (omitting the surrounding []'s), see also http://en.wikipedia.org/w/index.php?title=XPath_1.0&oldid=474981951.
* @param pred The predicate string, e.g. "name='BioSemi'" or "type='EEG' and starts-with(name,'BioSemi') and count(info/desc/channel)=32"
* @param minimum Return at least this number of streams.
* @param timeout Optionally a timeout of the operation, in seconds (default: no timeout).
*				  If the timeout expires, less than the desired number of streams (possibly none) will be returned.
* @return A vector of matching stream info objects (excluding their meta-data), any of 
*         which can subsequently be used to open an inlet.
*/
LIBLSL_CPP_API std::vector<stream_info> lsl::resolve_stream(const std::string &pred, int minimum, double timeout) {
	// create a new resolver
	resolver_impl resolver;
	// build a new query
	std::ostringstream os; os << "session_id='" << api_config::get_instance()->session_id() << "' and " << pred;
	// invoke it
	std::vector<stream_info_impl> tmp = resolver.resolve_oneshot(os.str(),minimum,timeout);
	return std::vector<stream_info>(tmp.begin(),tmp.end());
}


#include <daw/json/daw_json_iterator.h>
#include <daw/json/daw_json_link.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string_view>

struct coordinate_t {
	double x;
	double y;
	double z;
};

struct coordinates_t {
	std::vector<coordinate_t> coordinates;
};

namespace daw::json {
	template<>
	struct json_data_contract<coordinate_t> {
		using type =
		  json_member_list<json_number<"x">, json_number<"y">, json_number<"z">>;
	};

	template<>
	struct json_data_contract<coordinates_t> {
		using type = json_member_list<json_array<"coordinates", coordinate_t>>;
	};
} // namespace daw::json

std::string read_file( std::string const &filename ) {
	std::ifstream f( filename );
	if( !f ) {
		return { };
	}
	return std::string( std::istreambuf_iterator<char>( f ),
	                    std::istreambuf_iterator<char>( ) );
}

int main( int, char *[] ) {
	std::string const text = read_file( "test.json" );

	auto const json_sv = std::string_view( text.data( ), text.size( ) );
	double x = 0, y = 0, z = 0;
	int len = 0;

	using range_t = daw::json::json_array_range<coordinate_t, true>;
	auto rng = range_t( json_sv, "coordinates" );

	for( auto c : rng ) {
		++len;
		x += c.x;
		y += c.y;
		z += c.z;
	}
	std::cout << x / len << '\n';
	std::cout << y / len << '\n';
	std::cout << z / len << '\n';

	return 0;
}
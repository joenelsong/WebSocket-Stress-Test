//#include <limits.h>

#include "http_response.h"
#include <gtest/gtest.h>



/* RFC4648

   BASE64("") = ""
   BASE64("f") = "Zg=="
   BASE64("fo") = "Zm8="
   BASE64("foo") = "Zm9v"
   BASE64("foob") = "Zm9vYg=="
   BASE64("fooba") = "Zm9vYmE="
   BASE64("foobar") = "Zm9vYmFy"
*/

/* TEST(base64, RFC4648_empty {
	char* ans = (char*) "";
	unsigned char* inString = (unsigned char*) "";
	char *outBuffer = NULL;
	base64(inString, 0, &outBuffer);
	ASSERT_EQ(ans, outBuffer);
}
*/
TEST(base64, RFC4648_f) {
	char* ans = (char*) "Zg==";
	unsigned char* inString = (unsigned char*) "f";
	char *outBuffer = NULL;

   HTTP_Response::base64(inString, 1, &outBuffer);
	ASSERT_EQ(ans, outBuffer);

}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    
}

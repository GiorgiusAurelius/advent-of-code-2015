#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define FILE_NAME_MAX_LENGTH 9

int main() {

  CURL *curl;
  FILE *input;

  /*char *const_url1 = "https://adventofcode.com/2015/day/";
  char *const_url2 = "/input";

  char url[strlen(const_url1) + 2 + strlen(const_url2)];

  char input_day[3];
  char file_name[FILE_NAME_MAX_LENGTH] = "input.txt";

  printf("Provide the number of the day which input you need to download: \n");
  scanf("%2s", input_day);

  strcat(url, const_url1);
  strcat(url, input_day);
  strcat(url, const_url2);

  printf("Final constructed url: %s\n", url);

  */
  char *url = "https://adventofcode.com/2015/day/5/input";
  char file_name[FILE_NAME_MAX_LENGTH] = "input.txt";

  char *useragent = "https://github.com/GiorgiusAurelius/advent-of-code-2015/InputReader/input_reader.c by dmgiorgius@gmail.com";
  char *cookie_session = "53616c7465645f5f9fe308f2e38f2604619da60f84abd069f8af2cc1156b53576cacc45549ab0026562b437edb53fa9772e732c338bb3a91acec6ff2c819ac2d";

  // Initialize a libcurl easy handle
  curl = curl_easy_init();

  if (curl) {
    CURLcode res;
    if (input = fopen(file_name, "w+")) {
      // Setup the operation
      curl_easy_setopt(curl, CURLOPT_URL, url);
      curl_easy_setopt(curl, CURLOPT_USERAGENT, useragent);
      curl_easy_setopt(curl, CURLOPT_COOKIEFILE, cookie_session);
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, input);
      curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
      // Perform the operation
      res = curl_easy_perform(curl);
      // Check for errors
      if (res != CURLE_OK) {
        printf("curl_easy_perform() has failed: %s\n", curl_easy_strerror(res));
      }
      // cleanup
      curl_easy_cleanup(curl);
      fclose(input);
    } else {
      printf("Problem in opening the input file. The program ends.\n");
      return 0;
    } 
  }

  return EXIT_SUCCESS;
}
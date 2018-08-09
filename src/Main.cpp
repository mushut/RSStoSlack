#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

#include "RssItem.h"

int main(void)
{
	// Read file
	std::ifstream input_rss("/home/pi/unix/rss/rss_parse");
	std::ifstream input_number_of_items("/home/pi/unix/rss/number_of_items");
	std::ifstream data_from_csv("/home/pi/unix/rss/saved_data");

	// Read data from saved_data
	int how_many_values = 0;
	int how_many_items = 0;
	std::string new_value;
	std::string new_title;
	std::string new_contributor;
	std::string new_date;
	std::vector<RssItem> old_items;
	while (data_from_csv.good()) {
		if (how_many_values <= 3) {
			std::getline(data_from_csv,new_value,';');
			switch (how_many_values) {
				case 0:
					new_title = new_value;
					how_many_values++;
					break;
				case 1:
					new_contributor = new_value;
					how_many_values++;
					break;
				case 2:
					new_date = new_value;
					RssItem veryNewItem(new_title, new_contributor, new_date);
					old_items.push_back(veryNewItem);
					how_many_values = 0;
					how_many_items++;
					break;
			}
		}
	}

	// Store data to object
	std::vector<RssItem> items;
	std::string value;
	int number_of_values = 0;
	int item_counter = 0;
	int items_before = 0;
	std::string title;
	std::string contributor;
	std::string pubDate;
	while (input_rss.good()) {
		if (number_of_values <= 3) {
			std::getline(input_rss, value, ';');
			value.erase(std::remove(value.begin(), value.end(), '\n'), value.end());
			switch (number_of_values) {
				case 0:
					title = value;
					number_of_values++;
					break;
				case 1:
					contributor = value;
					number_of_values++;
					break;
				case 2:
					pubDate = value;
					RssItem newItem(title, contributor, pubDate);
					items.push_back(newItem);
					number_of_values = 0;
					item_counter++;
					break;
			}
		}
	}

	input_number_of_items >> items_before;

	// Close input streams
	input_rss.close();
	input_number_of_items.close();
	data_from_csv.close();

	// If there is new data, write it to new file
	std::ofstream output("/home/pi/unix/rss/rss_json.json");
	std::vector<RssItem> items_to_post;
	bool found = false;
	for (auto item : items) {
		found = false;
		for (auto iterator : old_items) {
			if (item.get_title() == iterator.get_title() && item.get_contributor() == iterator.get_contributor() && item.get_date() == iterator.get_date()) {
				found = true;
			}
		}
		if (found == false) {
			items_to_post.push_back(item);
		}
	}

	// Print start of the json file
	output << "{\"text\":\"";

	// Print items to file
	for (auto i : items_to_post) {
		output << i;
	}
	output << "\"}";

	// Close output stream
	output.close();

	std::ofstream saved_data("/home/pi/unix/rss/saved_data");

	for (auto i : items) {
		saved_data << i.toCsv();
	}

	saved_data.close();

	return 0;
}

#include <iostream>
#include <map>
#include <set>
#include <string>
#include <utility>

void UpdateNextUnvotedTrack(int& next_unvoted_track, const std::map<int, int>& tracks_score) {
  while (tracks_score.contains(next_unvoted_track)) {
    ++next_unvoted_track;
  }
}

int main() {
  auto comp = [](const std::pair<int, int>& x, const std::pair<int, int>& y) {
    if (x.second != y.second) {
      return x.second > y.second;
    }
    return x.first < y.first;
  };
  int next_unvoted_track{1};
  std::map<std::string, int> voter_last{};
  std::map<int, int> tracks_score{};
  std::set<std::pair<int, int>, decltype(comp)> queue{};

  std::string request{};
  std::cin >> request;
  while (request != "EXIT") {
    if (request == "VOTE") {
      std::string ip{};
      int track_id{};
      int delta_score{};
      int time{};
      std::cin >> ip >> track_id >> delta_score >> time;

      auto voter = voter_last.find(ip);
      if (voter == voter_last.end() || time - voter->second >= 600) {
        voter_last[ip] = time;
        auto track = tracks_score.find(track_id);
        if (track != tracks_score.end()) {
          queue.erase(std::make_pair(track->first, track->second));
          track->second += delta_score;
          queue.emplace(track->first, track->second);
        } else {
          tracks_score[track_id] = delta_score;
          queue.emplace(track_id, delta_score);
          if (next_unvoted_track == track_id) {
            UpdateNextUnvotedTrack(next_unvoted_track, tracks_score);
          }
        }
        std::cout << tracks_score[track_id] << '\n';
      } else {
        std::cout << (tracks_score.contains(track_id) ? tracks_score[track_id] : 0) << '\n';
      }
    } else {  // GET
      if ((queue.empty() || queue.begin()->second < 0 ||
           (queue.begin()->second == 0 && next_unvoted_track < queue.begin()->first)) &&
          next_unvoted_track <= 20000000) {
        std::cout << next_unvoted_track << ' ' << 0 << '\n';
        queue.emplace(next_unvoted_track, -1);
        tracks_score[next_unvoted_track] = -1;
        UpdateNextUnvotedTrack(next_unvoted_track, tracks_score);
      } else {
        int winner_id = queue.begin()->first;
        std::cout << winner_id << ' ' << queue.begin()->second << '\n';
        queue.erase(queue.begin());
        queue.emplace(winner_id, -1);
        tracks_score[winner_id] = -1;
      }
    }
    std::cin >> request;
  }
  std::cout << "OK\n";
  return 0;
}
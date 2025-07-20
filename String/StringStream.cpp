void marisa(){
    string s, cur;
    while(getline(cin, s)){
        stringstream ss(s); // 每个单词按照空格分割
        vector<string> words; // 存储所有单词
        while(ss >> cur){
            words.emplace_back(cur); // 放入所有单词
        }
    }
}
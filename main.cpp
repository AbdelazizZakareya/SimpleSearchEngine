#include "utility.h"
int main()
{
    int option;
    do
    {
        cout<<"Welcome!"<<endl;
        cout<<"What would you like to do? "<<endl;
        cout<<"1) New Search "<<endl;
        cout<<"2) Clear Screen "<<endl;
        cout<<"3) Exit "<<endl;
        cin>>option;
        switch(option)
        {
            case 1:
                newSearch();
                break;
            case 2:
                system("cls");
                break;
            case 3:
                break;
            default:
                cout<<"Enter a valid option "<<endl;
        }
    }
    while(option!=3);
    return 0;
}
void newSearch()
{
    vector<webGraph> webpages = getWebsites("fileTemp.csv");
    vector<vector<int>> adjMatrix = getAdjacencyMatrix("fileTemp.csv",webpages);
    calculatePageRank(adjMatrix,webpages);
    initialImpressions("NumberOfImpressions.csv",webpages);
    initialClicks(webpages);
    initialCTR(webpages);
    initialScore(webpages);
    vector<pair<string,string>> keyWords = getKeyWords("fileTemp2.csv");
    trieNode* root = getTrieNode();
    for(int i = 0; i<keyWords.size(); i++)
        insert(root,keyWords[i].first,keyWords[i].second);
    string key;
    cout<<"Enter the keywords "<<endl;
    cin>>key;
    if(key.find("OR") != string::npos)
        searchOR(root,key,webpages);
    else
        searchOR(root,key,webpages);
}
    /*
    if(search(root,key))
    {
        vector<string> web = getWebsitesOfKeyWord(root,key);
        set<string> set1;
        for(int i = 0; i<web.size(); i++)
            set1.insert(web[i]);
        vector<webGraph> web2;
        webGraph temp;
        for(auto x:set1)
        {
            temp.name = x;
            web2.push_back(temp);
        }
        for(int i = 0; i<web2.size();i++)
        {
            for(int j = 0; j<webpages.size();j++)
            {
                if(web2[i].name == webpages[j].name)
                {
                    web2[i] = webpages[j];
                    break;
                }
            }
        }
        cout<<"Zizo "<<endl;
        for(int i = 0; i<web2.size();i++)
            cout<<web2[i].name<<endl;
        cout<<"Impressions ";
        for(int i = 0; i<web2.size(); i++)
        {
            web2[i].impressions++;
            cout<<web2[i].impressions<<" ";
        }
        //Sorting according to score
        for(int i = 0; i<web2.size()-1;i++)
        {
            for(int j = 0; j<web2.size()-i-1;j++)
            {
                if(web2[j].score<web2[j+1].score)
                {
                    webGraph temp = web2[j];
                    web2[j] = web2[j+1];
                    web2[j+1] = temp;
                }
            }
        }
        cout<<"Zizo2 "<<endl;
        for(int i = 0; i<web2.size();i++)
            cout<<web2[i].name<<endl;
    }
    else
        cout<<"Not result "<<endl;

   
    */
    /*
    else if(response.find("AND") != string::npos)
        searchAND(root,response);
    else if(response.find("\"") != string::npos)
        searchQUOTES(root,response);
    
    */

/*
bool searchAND(trieNode* root, string keyWord)
{
    if()
}
*/
void searchOR(trieNode* root, string keyWord, vector<webGraph> webpages)
{
    trieNode* p = root;
    istringstream ss(keyWord);
    string word;
    vector<string> str;
    if (keyWord.find("\"") != string::npos)
    {
        keyWord.erase (keyWord.begin()+0);
        keyWord.erase (keyWord.end()-1);
    }
    while (ss >> word) 
    {
        str.push_back(word);
    }
    for(int i = 0; i<str.size();i++)
    {
        if(str[i] == "OR"||str[i] == "AND")
            str.erase(str.begin()+i);
    }

    if(search(p,str[0])== 1||search(p,str[1])==1);
    {
        vector<string> web0 = getWebsitesOfKeyWord(p,keyWord);
        vector<string> web1 = getWebsitesOfKeyWord(p,keyWord);
        set<string> set1;
        for(int i = 0; i<web0.size(); i++)
            set1.insert(web0[i]);
        for(int i = 1; i<web0.size(); i++)
            set1.insert(web1[i]);
        vector<webGraph> web2;
        webGraph temp;
        for(auto x:set1)
        {
            temp.name = x;
            web2.push_back(temp);
        }
        for(int i = 0; i<web2.size();i++)
        {
            for(int j = 0; j<webpages.size();j++)
            {
                if(web2[i].name == webpages[j].name)
                {
                    web2[i] = webpages[j];
                    break;
                }
            }
        }
        cout<<"Zizo "<<endl;
        for(int i = 0; i<web2.size();i++)
            cout<<web2[i].name<<endl;
        cout<<"Impressions ";
        for(int i = 0; i<web2.size(); i++)
        {
            web2[i].impressions++;
            cout<<web2[i].impressions<<" ";
        }
        //Sorting according to score
        for(int i = 0; i<web2.size()-1;i++)
        {
            for(int j = 0; j<web2.size()-i-1;j++)
            {
                if(web2[j].score<web2[j+1].score)
                {
                    webGraph temp = web2[j];
                    web2[j] = web2[j+1];
                    web2[j+1] = temp;
                }
            }
        }
        cout<<"Zizo2 "<<endl;
        for(int i = 0; i<web2.size();i++)
            cout<<web2[i].name<<endl;
    }
}
/*
bool searchQUOTES(trieNode* root, string keyWord)
{

}
*/
void calculatePageRank(vector<vector<int>>& adjMatrix, vector<webGraph>& webpages)
{
    int n = adjMatrix.size();
    int m = n*n;
    vector<int> numberEdges(n);
    for(int i = 0; i<n; i++)
        numberEdges[i] = 0;
    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<n; j++)
        {
            if(adjMatrix[i][j] == 1)
                numberEdges[i] += 1;
        }
    }
    vector<vector<double>> pageRank(n);
    for(int i = 0; i<n; i++)
        pageRank[i].resize(n);
    for(int i = 0; i<n;i++)
        pageRank[i][0] = 1/(double)n;
    for(int j = 1; j<n; j++)
    {
        for(int i =0; i<n;i++)
        {
            double sum = 0;
            for(int k = 0; k<n; k++)
            {
                if(adjMatrix[k][i] == 1)
                {
                    sum += (pageRank[k][j-1])/(double)numberEdges[k];
                }
            }
            pageRank[i][j] = sum;
        }
    }
    cout<<"Page Rank2 "<<endl;
    for(int i = 0; i<n;i++)
    {
        for(int j =0; j<n; j++)
        {
            cout<<pageRank[i][j]<<" ";
        }
        cout<<endl;
    }
    vector<double> finalPageRank(n);
    for(int i = 0; i<n; i++)
    {
        finalPageRank[i] = pageRank[i][n-1];
    }
    double min = *min_element(finalPageRank.begin(),finalPageRank.end());
    for(int i = 0; i<n; i++)
    {
        if(finalPageRank[i] == min)
            webpages[i].pageRank = 1;
        else
            webpages[i].pageRank = floor((finalPageRank[i])/min+1.0);
    }
    cout<<"Page Rank3 "<<endl;
    for(int i = 0; i<n;i++)
    {
        cout<<webpages[i].pageRank<<endl;
    }
    
}
vector<vector<int>> getAdjacencyMatrix(string file, vector<webGraph> webpages)
{
    vector<vector<int>> adjacencyList(webpages.size());
    vector<vector<int>> adjacencyMatrix(webpages.size());
    for(int i = 0; i <adjacencyMatrix.size();i++)
        adjacencyMatrix[i].resize(webpages.size());
    for(int i = 0; i<adjacencyMatrix.size();i++)
        for(int j = 0; j<adjacencyMatrix.size();j++)
            adjacencyMatrix[i][j] = 0;
    fstream myfile;
    myfile.open(file,ios::in);
    string line,word,temp;
    if(myfile.is_open())
    {
        while(!myfile.eof())
        {
            getline(myfile, line);
            stringstream s(line);
            int k = 0;
            while(getline(s,word,','))
            {
                if(k==0)
                    temp = word;
                else
                {
                    adjacencyList[searchIndex(temp,webpages)].push_back(searchIndex(word,webpages));
                }
                k++;
            }       
        }
        for(int i = 0; i<adjacencyMatrix.size();i++)
                for(int k = 0; k<adjacencyList[i].size();k++)
                    adjacencyMatrix[i][adjacencyList[i][k]] = 1;
        return adjacencyMatrix;
    }
    else
        cout<<"Unable to open file "<<endl;
}
int searchIndex(string keyword, vector<webGraph> webpages)
{
     for(int i = 0; i<webpages.size();i++)
     {
         if(keyword == webpages[i].name)
            return webpages[i].number;
    }
}
vector<webGraph> getWebsites(string file)
{
    fstream myfile;
    myfile.open(file,ios::in);
    string line,word;
    vector<webGraph> webpages;
    set<string> set1;
    if(myfile.is_open())
    {
        while(!myfile.eof())
        {
            getline(myfile, line);
            stringstream s(line);
            while(getline(s,word,','))
            {
                set1.insert(word); 
            }       
        }
        set<string>::iterator i;
        int j = 0;
        webpages.resize(set1.size());
        for(i = set1.begin(); i!=set1.end();i++)
        {
            webpages[j].name = *i;
            webpages[j].number = j;
            j++;
        }
        return webpages;
    }
    else
        cout<<"Unable to open file "<<endl;
}
void initialClicks(vector<webGraph>& webpages)
{
    for(int i = 0; i<webpages.size();i++)
        webpages[i].clicks = 0;
}
void updateClicks(vector<webGraph>& webpages, int i)
{
    webpages[i].clicks++;
}
void initialImpressions(string file, vector<webGraph>& webpages)
{
    fstream myfile;
    myfile.open(file,ios::in);
    string line,word,temp;
    int j = 0;
    if(myfile.is_open())
    {
        while(!myfile.eof())
        {
            getline(myfile, line);
            stringstream s(line);
            int k = 0;
            while(getline(s,word,','))
            {
                if(k==0)
                    temp = word;
                else
                {
                    webpages[j].impressions =  stoi(word);
                    j++;
                }       
                k++;
            }       
        }
        cout<<"Number of Impressions "<<endl;
        for(int i =0; i<webpages.size();i++)
            cout<<webpages[i].impressions<<endl;
    }
    else
        cout<<"Unable to open file "<<endl;
}
void initialScore(vector<webGraph>& webpages)
{
    for(int i = 0; i<webpages.size(); i++)
    {
        webpages[i].score = ( (0.4*webpages[i].pageRank) +
        0.6*( (1 - (0.1*webpages[i].impressions)/(1+0.1*webpages[i].impressions))*webpages[i].pageRank
        + webpages[i].ctr*(0.1*webpages[i].impressions)/(1+0.1*webpages[i].impressions)));
    }
}
void updateScore(vector<webGraph>& webpages, int i)
{
    webpages[i].score = ( (0.4*webpages[i].pageRank) +
        0.6*( (1 - (0.1*webpages[i].impressions)/(1+0.1*webpages[i].impressions))*webpages[i].pageRank
        + webpages[i].ctr*(0.1*webpages[i].impressions)/(1+0.1*webpages[i].impressions)));
}
void updateImpressions(vector<webGraph>& webpages, int i)
{
    webpages[i].impressions++;
}
void initialCTR(vector<webGraph>& webpages)
{
    for(int i = 0; i<webpages.size(); i++)
        webpages[i].ctr = 0;
}
void updateCRT(vector<webGraph>& webpages, int i)
{
    webpages[i].ctr++;
}
//PART2
//Inserting a new word in the trie data structure
void insert(trieNode* root, string keyWord, string website)
{
    trieNode* p = root;
    int index;
    for(int i = 0;i<keyWord.size();i++)
    {
        if(keyWord[i] - 'a' < 0)
            index = 'a' - keyWord[i]+25;
        else
            index = keyWord[i] - 'a';
        if(!p->children[index])
            p->children[index] = getTrieNode();
        p = p->children[index];
    }
        p->isEndOfWord = true;
        p->websites.push_back(website);
}
vector<string> getWebsitesOfKeyWord(trieNode* root, string keyWord)
{
    vector<string> web;
    trieNode* p = root;
    for(int i = 0; i<keyWord.size(); i++)
    {
        int index = keyWord[i] - 'a';
        p = p->children[index];
    }
    web = p->websites;
    return web;
}
vector<pair<string,string>> getKeyWords(string file)
{
    fstream myfile;
    myfile.open(file,ios::in);
    string line,word,temp;
    vector<pair<string,string>> keyWords;
    pair<string,string> p;
    if(myfile.is_open())
    {
        while(!myfile.eof())
        {
            getline(myfile, line);
            stringstream s(line);
            while(getline(s,word,','))
            {
                if(word.substr(0,3) == "www")
                    temp = word;
                else
                {
                    p.first = word;
                    p.second = temp;
                    keyWords.push_back(p);
                }
            }                
        }
        for(int i = 0;i<keyWords.size();i++)
            cout<<keyWords[i].first<<" "<<keyWords[i].second<<endl;
        return keyWords;
    }
    else
        cout<<"Unable to open file "<<endl;
}
bool search(trieNode* root, string keyWord)
{
    int index;
    trieNode* p = root;
    for(int i = 0; i<keyWord.size(); i++)
    {
        if(keyWord[i] - 'a' < 0)
            index = 'a' - keyWord[i]+25;
        else
            index = keyWord[i] - 'a';
        if(!p->children[index])
            return false;
        p = p->children[index];
    }
    return (p->isEndOfWord);
}
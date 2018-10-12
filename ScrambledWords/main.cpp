#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
#include <algorithm>
#include <cmath>
#include <ctime>

#define PR(x) cout << #x << ": " << x << endl;

using namespace std;

#define LARGE 100001
#define COMPILE false
#define TESTTIME false
#define ALPHA_LEN 26
#define num(x) (x - 'a')

char s[LARGE], gs[LARGE], hash[LARGE];
char S1, S2;
int N, A, B, C;
int alpha_array[ALPHA_LEN];

void printf_array(void* a, int num, char* name, char* type="int") {
  printf("Begin print content of %s:\n", name);
  int* b = NULL;
  long long* c = NULL;
  if (strcmp(type, "int") == 0) b = (int*)a; 
  else c = (long long*)a;
  for (int k = 0; k < num; k++) {
    if (strcmp(type, "int") == 0) printf("%d ", b[k]);
    else printf("%lld ", c[k]);
  }
  printf("\nAfter print content of %s.\n", name);
}

enum PointType {
  ROOT = 0,
  MIDDLE,
  START,
  END
};

class WordPoint {
public:
  // data
  char word; // current character
  char start_word; // take down the start word of this path
  char* content; // if this is a end point, take down the sequence
  PointType type; // root, start, mid, or end
  int lazy_mark; // to find if this end point is match before
  int length; // take down the current length from start point to here
  int hash_code; // take down the hash code from start to here
  class FailedPointer {
  public:
    FailedPointer() : start_word(0), length(0), hash_code(0), next(NULL) {}
    char start_word;
    int length;
    int hash_code;
    WordPoint* next;
  };
  vector<FailPointer*> fp_array;
  vector<WordPoint*> childs;

  // method
  WordPoint(char c) : word(c), type(ROOT), start_word(0), lazy_mark(0), length(0), hash_code(0), content(NULL) {
    fp_array.clear();
    childs.clear();
  }
  ~WordPoint() {
    for (int i = 0; i < childs.size(); i++) delete childs[i];
    childs.clear();
    fp_array.clear();
  }
};

class WordTree {
public:
  // data
  WordPoint* root;

  // method
  WordTree() { root = NULL; }
  ~WordTree() { delete root; }
  int value_index(WordPoint* p, char* c);
  void add_tree(char s[]);
  void set_failed_pointer();
  void get_failed_pointer_from_point(WordPoint::FailedPointer* fp, WordPoint* p);
  void match_word(WordPoint* p, char c, int rank, int &count);
  int process(char S1, char S2, int N, int A, int B, int C);
};

int WordTree:value_index(WordPoint* p, char c) {
  for (int i = 0; i < p->childs.size(); i++) 
    if (p->childs[i]->word == c)
      return i;
  return -1;
}

void WordTree::add_tree(char s[]) {
  // sort s with [1, -1), here 2 <= len(s)
  lens = strlen(s);
  // time used: klogk
  sort(s[1], s[lens - 1]);
  WordPoint* cp = root, *np;
  int rank = 0;
  // k
  while (s[rank]) {
    int index = value_index(cp, s[rank]);
    if (index < 0) {
      np = new WordPoint(s[rank]);
      if (rank == 0) {
        np->start_word = s[rank];
        np->length = 1;
        np->hash_code = 0;
        np->type = START;
      } else {
        np->start_word = cp->start_word;
        np->length = cp->length + 1;
        np->hash_code += s[rank];
        if (rank == lens - 1) {
          np->type = END;
          np->content = s;
        } else np->type = MIDDLE;
      } 
      cp->childs.push_back(np);
    } else {
      np = cp->childs[index];
      if (rank == lens - 1) { 
        np->type = END;
        np->content = s;
      }
    }
    cp = np;
    // rank++
    rank++;
  }
}

void WordTree::get_failed_pointer_from_point(WordPoint::FailedPointer* fp, WordPoint* p) {
  fp = new WordPoint::FailedPointer;
  fp->next = p;
  fp->start_word = p->word;
  fp->length = p->length;
  fp->hash_code = p->hash_code;
}

void WordTree::set_failed_pointer() {
  queue<WordPoint*> q;
  q.push(root);
  while (!q.empty()) {
    WordPoint* cp = q.front();
    q.pop();
    for (int i = 0; i < cp->childs.size(); i++) {
      WordPoint* child = cq->childs[i];
      q.push(child);
      if (cp == root) {
        WordPoint::FailedPointer* fp = new WordPoint::FailedPointer;
        fp->next = root;
        child->fp_array.push_back(fp);
      } else {
        for (int i = 0; i < cp->fp_array.size(); i++) {
          WordPoint::FailedPointer* fp = cp->fp_array[i];
          WordPoint* nfp = fp->next;
          WordPoint::FailedPointer* lfp;
          for (int i = 0; i < nfp->childs.size(); i++) {
            lfp = NULL;
            cfp = nfp->childs[i];
            if (nfp == root) {
              if (cfp->word == child->word) {
                get_failed_pointer_from_point(lfp, cfp);
                child->fp_array.push_back(lfp);
              }
            } else if (cfp->hash_code == child->hash_code) {
              get_failed_pointer_from_point(lfp, cfp);
              child->fp_array.push_back(lfp);
            }
          }
        }
        if (child->fp_array.size() <= 0) {
          WordPoint::FailedPointer* fp = new WordPoint::FailedPointer;
          fp->next = root;
          child->fp_array.push_back(fp);
        }
      }
    }
  }
}

char generate_word(char a, char b) {
  long long d = ((long long)A * (int)a + (long long)B * (int)b + (long long)C) % D;
  return char(97 + (d % 26));
}

void WordTree::loop_failed_pointer(WordPoint* p, int rank, int& count) {
  if (p == root) return;
  // scanf each fp_array, only when start, len, hash_code, lazy_mark all match, track each point
  for (int i = 0; i < p->fp_array.size(); i++) {
    WordPoint::FailedPointer* fp = p->fp_array[i];
    int start_rank = rank - fp->length + 1;
    // test length and start point
    if (gs[start_rank] == fp->start_word) {
      // test hash code
      int h = hash[rank] - hash[start_rank];
      if (h == fp->hash_code) {
        WordPoint* np = fp->next;
        // if end point, to see if it is right
        if (np->type == END) {
          // to see if it mark lazy, which means checked before
          if (np->lazy_mark == 0) {
            // match each word
            bool matched = true;
            for (int i = 0; i < strlen(np->content); i++) {
              if (np->content[i] != gs[start_rank + i]) {
                matched = false;
                break;
              }
            }
            if (matched) {
              count++;
              np->lazy_mark = 1;
            }
          }
        }
        loop_failed_pointer(np);
      }
    }
  }
}

void WordTree::match_word(WordPoint* p, char c, int rank, int& count) {
  for (int i = 0; i < p->childs.size(); i++) {
    WordPoint* child = p->childs[i];
    if (child->word == c) {
      alpha_array[num(c)]--;
      // get all the failed pointer that is root
      loop_failed_pointer(p, rank, count);
      // check current point
      if (p->type == END) {
        count++;
        p->lazy_mark = 1;
      }
      p = child;
      return;
    }
  }
  WordPoint *np = p;
  while (true) {
    
  }
}

int WordTree::process() {
  int rank = 0, count = 0; 
  queue<WordPoint*> res;
  // initialize x1, x2 and tree
  char a, b, c;
  WordPoint* cp = root;
  memset(alpha_array, 0, sizeof(alpha_array));
  while (rank < N) {
    // get current insert word, this word need to be the end
    if (rank == 0) { c = S1; }
    else if (rank == 1) { a = S1, b = S2, c = S2; }
    else c = generate_word(a, b);
    gs[rank] = c;
    hash[rank] = (rank == 0) ? 0 : hash[rank] + c;
    alpha_array[num(c)]++;
    // get all the has result with this end
    match_word(cp, c, rank, count);
    // if not child match
    // take the root into account
  }
}

int main(int argc, char** argv) {
  char* def_ifn = "large.in";
  char* def_ofn = "large.out";
  if (1 < argc) def_ifn = argv[1];
  if (2 < argc) def_ofn = argv[2];
  freopen(def_ifn, "r", stdin);
  freopen(def_ofn, "w", stdout);
  int T = 0, i = 0;
  scanf("%d", &T);
  if (COMPILE) printf("Get T: %d\n", T);
  while (i++ < T) {
    clock_t st = clock();
    WordTree tree;
    int L = 0, j = 0;
    while (j++ < L) {
      scanf("%s", s);
      // Add current s to tree
      tree->add_tree(s);
    }
    // set failed pointer here
    tree->set_failed_pointer();
    scanf("%c %c %d %d %d %d", &S1, &S2, &N, &A, &B, &C);
    // generate word and get result in tree
    int res = tree->process(S1, S2, N, A, B, C);
    if (TESTTIME) printf("With Case %d.\n", i);
    clock_t rt = clock();
    if (TESTTIME) printf("Read in data takes time: %f seconds\n", ((float)(rt - st)) / CLOCKS_PER_SEC);
    if (COMPILE) printf_array(ini_array, 0, "ini_array", "int");
    printf("Case #%d: %d\n", i, res);
  }
  return 0;
}

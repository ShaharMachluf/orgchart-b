#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <iostream>

namespace ariel{
    struct Tree{
        std::string data;
        std::vector<Tree*> children;
    };

    class OrgChart{
        struct Tree *root;
        public:
        class Iterator{
            struct Tree *ptr;
            std::string order;
            std::queue<struct Tree*> q;
            std::stack<struct Tree*> s;
            void preorder(struct Tree* node);
            public:
            Iterator();
            Iterator(const OrgChart &o ,std::string order);
            Iterator& operator++();
            std::string operator*();
            bool operator==(Iterator other);
            bool operator!=(Iterator other);
            Iterator& operator=(Iterator &other);
            std::string* operator->();
            struct Tree* get_node();
        };
        OrgChart();
        OrgChart& add_root(std::string s);
        OrgChart& add_sub(std::string sup, std::string inf);

        Iterator begin() const;
        Iterator end() const;
        Iterator begin_level_order() const;
        Iterator end_level_order() const;

        Iterator begin_reverse_order();
        Iterator reverse_order();

        Iterator begin_preorder();
        Iterator end_preorder();

        friend std::ostream& operator<<(std::ostream& output, const OrgChart& other);
    };
}
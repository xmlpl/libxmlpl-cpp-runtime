#include "Node.h"
#include "Element.h"
#include "Attribute.h"
#include "Text.h"
#include "Comment.h"
#include "PI.h"
#include "QName.h"
#include "String.h"

#include <iostream>

using namespace std;
using namespace xmlpl;

int main(int argc, char *argv[]) {
	cout << "sizeof(Node) = "      << sizeof(Node) << endl;
	cout << "sizeof(Element) = "   << sizeof(Element) << endl;
	cout << "sizeof(Attribute) = " << sizeof(Attribute) << endl;
	cout << "sizeof(Text) = "      << sizeof(Text) << endl;
	cout << "sizeof(Comment) = "   << sizeof(Comment) << endl;
	cout << "sizeof(PI) = "        << sizeof(PI) << endl;
	cout << "sizeof(QName) = "     << sizeof(QName) << endl;
	cout << "sizeof(String) = "    << sizeof(String) << endl;

	return 0;
}

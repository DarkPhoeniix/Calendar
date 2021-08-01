#pragma once
#include <iostream>
#include <memory>
#include <map>

#include "Node.h"
#include "Token.h"

std::shared_ptr<Node> parseCondition(std::istream& in);

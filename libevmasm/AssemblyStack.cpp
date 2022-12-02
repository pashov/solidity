/*
	This file is part of solidity.

	solidity is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	solidity is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with solidity.  If not, see <http://www.gnu.org/licenses/>.
*/
// SPDX-License-Identifier: GPL-3.0

#include <libevmasm/AssemblyStack.h>

#include <liblangutil/Exceptions.h>
#include <libsolidity/codegen/CompilerContext.h>

#include <utility>

using namespace solidity::langutil;
using namespace solidity::frontend;
using namespace std;

namespace solidity::evmasm
{

AssemblyStack::AssemblyStack(std::string _name, Json::Value _json): m_name(std::move(_name)), m_json(std::move(_json))
{
}

void AssemblyStack::assemble()
{
	m_evmAssembly = evmasm::Assembly::loadFromAssemblyJSON(m_json);
	solAssert(m_evmAssembly->isCreation() == true);
	m_object = m_evmAssembly->assemble();
	m_evmRuntimeAssembly = make_shared<evmasm::Assembly>(m_evmAssembly->sub(0));
	solAssert(m_evmRuntimeAssembly->isCreation() == false);
	m_runtimeObject = m_evmRuntimeAssembly->assemble();
}

map<string, unsigned> AssemblyStack::sourceIndices() const
{
	map<string, unsigned> indices;
	unsigned index = 0;
	for (auto const& s: m_evmAssembly->sources())
		if (*s != CompilerContext::yulUtilityFileName())
			indices[*s] = index++;
	if (indices.find(CompilerContext::yulUtilityFileName()) == indices.end())
		indices[CompilerContext::yulUtilityFileName()] = index++;
	return indices;
}

std::optional<std::string> AssemblyStack::sourceMapping()
{
	std::optional<std::string const> result;
	if (!m_evmRuntimeAssembly->items().empty())
		result.emplace(evmasm::AssemblyItem::computeSourceMapping(m_evmAssembly->items(), sourceIndices()));
	return result;
}

std::optional<std::string> AssemblyStack::runtimeSourceMapping()
{
	std::optional<std::string const> result;
	if (!m_evmRuntimeAssembly->items().empty())
		result.emplace(evmasm::AssemblyItem::computeSourceMapping(m_evmRuntimeAssembly->items(), sourceIndices()));
	return result;
}

} // namespace solidity::evmasm

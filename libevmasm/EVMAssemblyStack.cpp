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

#include <libevmasm/EVMAssemblyStack.h>

#include <liblangutil/Exceptions.h>
#include <libsolidity/codegen/CompilerContext.h>

#include <utility>

using namespace solidity::langutil;
using namespace solidity::frontend;
using namespace std;

namespace solidity::evmasm
{

EVMAssemblyStack::EVMAssemblyStack(std::string _name, Json::Value _json):
	m_name(std::move(_name)),
	m_json(std::move(_json))
{
	m_evmAssembly = evmasm::Assembly::fromJSON(m_json, {}, 0);
	solAssert(m_evmAssembly);
}

void EVMAssemblyStack::assemble()
{
	solAssert(m_evmAssembly->isCreation());
	m_object = m_evmAssembly->assemble();
//	solRequire(m_evmAssembly->numSubs() <= 1, AssemblyImportException, "You can only have exactly one or none subroutine(s).");
	if (m_evmAssembly->numSubs() > 0)
	{
		m_evmRuntimeAssembly = make_shared<evmasm::Assembly>(m_evmAssembly->sub(0));
		solAssert(m_evmRuntimeAssembly && !m_evmRuntimeAssembly->isCreation());
		m_runtimeObject = m_evmRuntimeAssembly->assemble();
	}
}

} // namespace solidity::evmasm

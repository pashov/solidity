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

#pragma once

#include <map>
#include <string>

#include <libsolutil/JSON.h>

#include <libevmasm/Assembly.h>
#include <libevmasm/LinkerObject.h>

namespace solidity::evmasm
{

class AssemblyStack
{
public:
	explicit AssemblyStack(std::string _name, Json::Value _json);

	void assemble();

	std::string const& name() { return m_name; }

	evmasm::LinkerObject const& object() { return m_object; }

	std::shared_ptr<evmasm::Assembly> const& evmAssembly() const { return m_evmAssembly; }

	evmasm::LinkerObject const& runtimeObject() { return m_runtimeObject; }

	std::shared_ptr<evmasm::Assembly> const& evmRuntimeAssembly() const { return m_evmRuntimeAssembly; }

	std::map<std::string, unsigned> sourceIndices() const;

	std::optional<std::string> sourceMapping();

	std::optional<std::string> runtimeSourceMapping();

private:
	std::string m_name;
	Json::Value m_json;
	std::shared_ptr<evmasm::Assembly> m_evmAssembly;
	std::shared_ptr<evmasm::Assembly> m_evmRuntimeAssembly;
	evmasm::LinkerObject m_object; ///< Deployment object (includes the runtime sub-object).
	evmasm::LinkerObject m_runtimeObject; ///< Runtime object.
};

} // namespace solidity::evmasm

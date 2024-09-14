/**
 * @file: HTTPNetworkTransport.cpp
 * @author: Ammar Massoud (ammar@wpkama.com)
 * 
 * @brief
 *     This file implements class HTTPNetworkTransport::HTTPNetworkTransport
 * 
 * @version: 1.0.0
 * @date: 2024-07-28
 * @copyright: Copyright (c) 2024
 */

#include <HTTPNetworkTransport/HTTPServerNetworkTransport.hpp>

namespace HTTPNetworkTransport
{
	/**
	 * @brief
	 *     This contains all private properties of the client class.
	 */
	struct HTTPNetworkTransport::Impl
	{
	};

	HTTPNetworkTransport::~HTTPNetworkTransport() = default;

	HTTPNetworkTransport::HTTPNetworkTransport(): impl_(new Impl())
	{}
} // namespace HTTPNetworkTransport

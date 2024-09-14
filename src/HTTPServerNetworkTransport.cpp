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
	struct HTTPServerNetworkTransport::Impl
	{
	};

	HTTPServerNetworkTransport::~HTTPServerNetworkTransport() = default;

	HTTPServerNetworkTransport::HTTPServerNetworkTransport(): impl_(new Impl())
	{}

	bool HTTPServerNetworkTransport::bindNetwork(
		uint16_t port,
		NewConnectionDelegate newConnectionDelegate
	) {
		return impl_->endpoint.Open(
			[this, newConnectionDelegate](std::shared_ptr<SystemAbstractions::NetworkConnection> newConnection)
			{
				const auto adapter = std::make_shared<ConnectionAdapter>();
				adapter->adaptee = newConnection;
				if (!adapter->wireUpAdapter())
					return;
				newConnectionDelegate(adapter);
			},
			[this](
				uint32_t address,
				uint16_t port,
				const std::vector<uint8_t> &body) {
				// NODE: This function we never be called, because it's only
				// used in datagram-oriented network endpoints, and this explicitly
				// configured to be a connection-oriented endpoint.
			},
			SystemAbstractions::NetworkEndpoint::Mode::Connection,
			0,
			0,
			port);
	}

	void HTTPServerNetworkTransport::releaseNetwork()
	{
		impl_->endpoint.Close();
	}

	void HTTPServerNetworkTransport::setNewConnectionDelegate(
		NewConnectionDelegate delegate
	) {

	}

	uint16_t HTTPServerNetworkTransport::getBoundPort()
	{
		return impl_->endpoint.GetBoundPort();
	}
} // namespace HTTPNetworkTransport

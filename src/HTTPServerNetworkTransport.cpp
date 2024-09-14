/**
 * @file: HTTPNetworkTransport.cpp
 * @author: Ammar Massoud (ammar@wpkama.com)
 * 
 * @brief
 *     This file implements class 
 *     HTTPNetworkTransport::HTTPServerNetworkTransport
 * 
 * @version: 1.0.0
 * @date: 2024-07-28
 * @copyright: Copyright (c) 2024
 */

#include <HTTPNetworkTransport/HTTPServerNetworkTransport.hpp>
#include <SystemAbstractions/NetworkEndpoint.hpp>

namespace {
	/**
	 * @brief
	 *     This class is an adapter between two related classes
	 *     in different libraries
	 *     - HTTP::Connection -- the interface required by HTTP
	 *       library for sending & receiving data across the transport
	 *       layer.
	 *     - SystemAbstractions::NetworkConnection -- the class which
	 *       implements a connection object in terms of the operating
	 *       system's network APIs.
	 */
	struct ConnectionAdapter: public HTTP::Connection
	{
		// Properties

		/**
		 * @brief
		 *     This is the object which is implementing the network
		 *     connection in terms of the operating system's network APIs.
		 */
		std::shared_ptr<SystemAbstractions::NetworkConnection> adaptee;

		/**
		 * @brief
		 *     This is the callback to call whenever data is received from
		 *     the remote peer.
		 */
		DataReceivedDelegate dataReceivedDelegate;

		/**
		 * @brief
		 *     This is the callback to call whenever the connection
		 *     has been broken.
		 */
		BrokenDelegate brokenDelegate;

		// Methods

		/**
		 * @brief
		 *     This method should be called once the adapter is in place.
		 *     it fires up the actual network processing.
		 * 
		 * @returns
		 *     true if the adapter processing is successfully started,
		 *     otherwise false is returned.
		 */
		bool wireUpAdapter() {
			return adaptee->Process(
				[this](const std::vector<uint8_t> &message)
				{
					if (dataReceivedDelegate != nullptr)
						dataReceivedDelegate(message);
				},
				[this](bool graceful)
				{
					if (brokenDelegate != nullptr)
						brokenDelegate();
				}
			);
		}

		// HTTP::Connection

		/**
		 * @brief
		 *     This method sets the callback to call whenever data is received
		 *     from the remote peer.
		 * 
		 * @param[in] delegate
		 *     This is the callback to call whenever data is received from
		 *     the remote peer.
		 */
		virtual void setDataReceivedDelegate(DataReceivedDelegate delegate) override {
			dataReceivedDelegate = delegate;
		};

		/**
		 * @brief
		 *     This method sets the callback to call whenever the connection
		 *     has been broken.
		 * 
		 * @param[in] delegate
		 *     This is the callback to call whenever the connection
		 *     has been broken.
		 */
		virtual void setBrokenDelegate(BrokenDelegate delegate) override {
			brokenDelegate = delegate;
		}

		/**
		 * @brief
		 *     This method sends the given data to the remote peer.
		 * 
		 * @param[in] data
		 *     This is the data to send to the remote peer.
		 */
		virtual void sendData(std::vector<uint8_t> data) override {
			adaptee->SendMessage(data);
		}

		/**
		 * @brief
		 *     This method breaks the connection with the remote peer.
		 * 
		 * @param[in] clean
		 *     indicates whether or not to complete any data transmission
		 *     still in progress, before breaking the connection.
		 */
		virtual void breakConnection(bool clean) override {
			// TODO: if clean == true, we need to hold off until adapter
			// has written all its data.
			adaptee->Close();
		}
	};
}

namespace HTTPNetworkTransport
{
	/**
	 * @brief
	 *     This contains all private properties of the
	 *     HTTPServerNetworkTransport class.
	 */
	struct HTTPServerNetworkTransport::Impl
	{
		// Properties

		/**
		 * @brief
		 *     This is used to implement the transport layer.
		 */
		SystemAbstractions::NetworkEndpoint endpoint;

		// Methods
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

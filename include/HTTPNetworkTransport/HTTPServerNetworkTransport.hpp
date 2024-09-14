#ifndef __HTTP_NETWORK_TRANSPORT_HPP__
#define __HTTP_NETWORK_TRANSPORT_HPP__

#include <memory>
#include <HTTP/ServerTransport.hpp>

/**
 * @file: HTTPNetworkTransport.hpp
 * @author: Ammar Massoud (ammar@wpkama.com)
 * 
 * @brief
 *     This file declares class HTTPNetworkTransport::HTTPNetworkTransport
 * 
 * @version: 1.0.0
 * @date: 2024-07-28
 * @copyright: Copyright (c) 2024
 */

namespace HTTPNetworkTransport
{
	/**
	 * @brief
	 *     This is an implementation of HTTP::ServerTransport
	 *     that uses real network available through the operating
	 *     system.
	 */
	class HTTPServerNetworkTransport
		: public HTTP::ServerTransport
	{
	public:
		// Lifecycle Management
		
		~HTTPServerNetworkTransport() noexcept;
		HTTPServerNetworkTransport(const HTTPServerNetworkTransport &) noexcept = delete;
		HTTPServerNetworkTransport(HTTPServerNetworkTransport &&) noexcept = delete;
		HTTPServerNetworkTransport &operator=(const HTTPServerNetworkTransport &) noexcept = delete;
		HTTPServerNetworkTransport &operator=(HTTPServerNetworkTransport &&) noexcept = delete;

		// Public Methods
		
		/**
		 * @brief
		 *     Construct a new HTTPServerNetworkTransport object
		 */
		HTTPServerNetworkTransport();

		// HTTP::ServerTransport
		
		/**
		 * @brief
		 *     This method acquires exclusive access to the given port
		 *     on all network interface, and begins the process of listening
		 *     for and accepting incoming connections from clients.
		 * 
		 * @param[in] port
		 *     This is the public port number to which clients may connect
		 *     to establish connections with this server.
		 * 
		 * @param[in] delegate
		 *     callback to be called whenever a new connection has
		 *     been established for the server.
		 * 
		 * @return
		 *     true if the connection is already established successfully
		 *     otherwise false is returned.
		 */
		virtual bool bindNetwork(
			uint16_t port,
			NewConnectionDelegate delegate
		) override;

		/**
		 * @brief
		 *     This method returns the public port number that was
		 *     bound for accepting connections from clients.
		 * 
		 * @return
		 *     The public port number that was bound for accepting
		 *     connections from clients.
		 */
		virtual uint16_t getBoundPort() override;

		/**
		 * @brief
		 *     This method releases all resources and access that were
		 *     acquired and held as a result of calling bindNetwork method.
		 */
		virtual void releaseNetwork() override;

		/**
		 * @brief
		 *     This method sets the callback to call whenever a new
		 *     connection has been established for the server.
		 * 
		 * @param[in] delegate
		 *     callback to be called whenever a new connection has
		 *     been established for the server.
		 */
		virtual void setNewConnectionDelegate(NewConnectionDelegate delegate) override;

	private:
		// Private Properties
		/**
		 * @brief
		 *     structure to hold all the private properties of the
		 *     HTTPServerNetworkTransport instance.
		 */
		struct Impl;

		/**
		 * @brief
		 *     This contains all private properties of the HTTPServerNetworkTransport
		 *     class.
		 */
		std::unique_ptr<struct Impl> impl_;
	};
} // namespace HTTPNetworkTransport

#endif /* __HTTP_NETWORK_TRANSPORT_HPP__ */